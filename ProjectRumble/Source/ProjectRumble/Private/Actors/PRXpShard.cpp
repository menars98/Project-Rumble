// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PRXpShard.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"


APRXpShard::APRXpShard()
{
	PrimaryActorTick.bCanEverTick = true; 

	// Create basic components
	//DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent = DefaultSceneRoot;
	// TODO: Create StaticMesh and SphereCollision components here

}

void APRXpShard::StartHoming(APRCharacterBase* Target)
{
	// If we are already homing towards something, don't change target.
	if (!HomingTarget)
	{
		HomingTarget = Target;
	}
}

void APRXpShard::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("XPShard Ready!"));
}

void APRXpShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If we have a target, move towards it.
	if (HomingTarget)
	{
		// Calculate the new location by interpolating towards the target
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = HomingTarget->GetActorLocation();
		FVector NewLocation = UKismetMathLibrary::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, HomingSpeed / 1000.f); // InterpSpeed is a factor, not absolute speed

		SetActorLocation(NewLocation);

		// Check if we have reached the target
		const float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);
		if (DistanceToTarget < 100.f) // If we are close enough
		{
			// Grant XP
			if (APRPlayerState* PS = HomingTarget->GetPlayerState<APRPlayerState>())
			{
				if (UPRStatsComponent* StatsComp = PS->StatsComponent)
				{
					StatsComp->AddXP(XPValue);
				}
			}

			// Destroy self
			Destroy();
		}
	}
}


