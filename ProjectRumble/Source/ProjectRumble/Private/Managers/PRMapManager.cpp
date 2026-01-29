// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRMapManager.h"
#include "Datas/Map/PRMapGenDefinition.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/KismetSystemLibrary.h"


APRMapManager::APRMapManager()
{
	bReplicates = true;

	SpawnAreaBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnAreaBox"));
	RootComponent = SpawnAreaBox;
	SpawnAreaBox->SetBoxExtent(FVector(2500.f, 2500.f, 100.f)); // Default size
	SpawnAreaBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void APRMapManager::BeginPlay()
{
	Super::BeginPlay();

	// Since chests are “Replicated Actors,” they should ONLY be spawned on the SERVER.
	if (HasAuthority())
	{
		// @TODO: Maybe more controlled seeding?
		MapSeed = FMath::Rand(); 

		SpawnInteractables();
	}
	
}

void APRMapManager::OnRep_MapSeed()
{
}

void APRMapManager::GenerateMap()
{
}

void APRMapManager::SpawnStaticEnvironment(FRandomStream& Stream)
{
}

void APRMapManager::SpawnInteractables()
{
    if (!MapDefinition) return;

    FRandomStream Stream(MapSeed);

	// Temporary list to track spawned locations for distance checks
    TArray<FVector> SpawnedLocations;

    for (const FInteractableSpawnRule& Rule : MapDefinition->Interactables)
    {
        if (!Rule.ActorClass) continue;

        int32 SpawnedCount = 0;
        int32 MaxRetries = 20; // For safety

        // Loop
        while (SpawnedCount < Rule.SpawnCount)
        {
            FVector CandidateLocation = FVector::ZeroVector;
            bool bFoundValidSpot = false;

            // --- Retry ---
            for (int32 i = 0; i < MaxRetries; ++i)
            {
                FVector TestLoc = GetRandomGroundLocation(Stream);

                if (TestLoc == FVector::ZeroVector) continue; // Zemin yoksa geç

                // Distance Control
                bool bTooClose = false;
                float MinDistSq = Rule.MinDistanceBetween * Rule.MinDistanceBetween;

                for (const FVector& ExistingLoc : SpawnedLocations)
                {
                    if (FVector::DistSquared(TestLoc, ExistingLoc) < MinDistSq)
                    {
                        bTooClose = true;
                        break;
                    }
                }

				// Found a valid spot
                if (!bTooClose)
                {
                    CandidateLocation = TestLoc;
                    bFoundValidSpot = true;
                    break; // Break
                }
            }
            // ------------------------------

            if (bFoundValidSpot)
            {
                // Spawn
                FActorSpawnParameters Params;
                Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

                GetWorld()->SpawnActor<AActor>(Rule.ActorClass, CandidateLocation, FRotator::ZeroRotator, Params);

				// Add to spawned list
                SpawnedLocations.Add(CandidateLocation);
                SpawnedCount++;
            }
            else
            {
				// Could not find a valid spot after retries
                UE_LOG(LogTemp, Warning, TEXT("MapManager: Could not find valid spot for %s after retries."), *Rule.ActorClass->GetName());
                break;
            }
        }
    }
}

FVector APRMapManager::GetRandomGroundLocation(const FRandomStream& Stream) const
{
	// 1. Select a random X,Y within the Spawn Area
    FVector Origin = GetActorLocation();
    FVector BoxExtent = SpawnAreaBox->GetScaledBoxExtent();

    // Should we use the size in MapDefinition or the Box Component?
    // The Box Component is more visual.
    float RandomX = Stream.FRandRange(-BoxExtent.X, BoxExtent.X);
    float RandomY = Stream.FRandRange(-BoxExtent.Y, BoxExtent.Y);

    FVector StartTrace = Origin + FVector(RandomX, RandomY, 1000.0f); // Yukarýdan baþla
    FVector EndTrace = Origin + FVector(RandomX, RandomY, -1000.0f);  // Aþaðýya in

	// 2. Find the ground using a line trace
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit,
        StartTrace,
        EndTrace,
        ECC_Visibility, 
        Params
    );

    if (bHit)
    {
		return Hit.Location; // Ground found
    }

	return FVector::ZeroVector; // No ground found
}

void APRMapManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APRMapManager, MapSeed);
}


