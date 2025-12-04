#include "Actors/PRPickupBase.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"
#include "Components/PRLootComponent.h"
#include "Net/UnrealNetwork.h"

APRPickupBase::APRPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);
}

void APRPickupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APRPickupBase, Value);
	DOREPLIFETIME(APRPickupBase, HomingTarget);
}

void APRPickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void APRPickupBase::StartHoming(APRCharacterBase* Target)
{
	// If we are NOT already homing, lock on to the target.
	if (GetLocalRole() == ROLE_Authority)
	{
		if (!bIsHoming && Target)
		{
			HomingTarget = Target;
			bIsHoming = true;

			// --- INITIALIZE THE SPEED ---
			// When homing starts, set the current speed to the initial speed.
			CurrentHomingSpeed = InitialHomingSpeed;

			// We can close server side pyhsics if needed
			// (StaticMesh -> SetSimulatePhysics(false)

			UE_LOG(LogTemp, Log, TEXT("XP Shard is now homing to player."));
		}
	}
	

}

void APRPickupBase::OnRep_HomingTarget()
{
	
	if (HomingTarget)
	{
		bIsHoming = true;
		CurrentHomingSpeed = InitialHomingSpeed;
		// We can play vfx/sfx here on clients if needed
	}
}

void APRPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// --- ADD THIS LOG ---
	UE_LOG(LogTemp, Log, TEXT("PickupBase Tick is running for %s..."), *GetName());

	// If we have a target, move towards it.
	if (bIsHoming  && HomingTarget)
	{
		// --- 1. ACCELERATE ---
		// Increase the current speed over time, but don't exceed the max speed.
		CurrentHomingSpeed = FMath::FInterpTo(
			CurrentHomingSpeed,
			MaxHomingSpeed,
			DeltaTime,
			HomingAcceleration
		);

		// --- 2. MOVE ---
		// Calculate the new location by moving towards the target at the CURRENT speed.
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation = HomingTarget->GetActorLocation();
		FVector DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
		
		FVector NewLocation = CurrentLocation + (DirectionToTarget * CurrentHomingSpeed * DeltaTime);
		SetActorLocation(NewLocation);

		// Check against a squared distance to avoid expensive Sqrt calculation
		if (HasAuthority())
		{
			// --- 3. CHECK FOR ARRIVAL ---
			const float DistanceToTarget = FVector::DistSquared(CurrentLocation, TargetLocation);
			if (DistanceToTarget < FMath::Square(100.f))
			{
				// Call the overridable function
				OnCollected();
				Destroy();
			}
		}
	}
}

void APRPickupBase::OnCollected_Implementation()
{

}