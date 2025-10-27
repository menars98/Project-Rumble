#include "Actors/PRPickupBase.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"
#include "Components/PRLootComponent.h"

APRPickupBase::APRPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APRPickupBase::BeginPlay()
{
	Super::BeginPlay();
}

void APRPickupBase::StartHoming(APRCharacterBase* Target)
{
	// If we are NOT already homing, lock on to the target.
	if (!bIsHoming && Target)
	{
		HomingTarget = Target;
		bIsHoming = true;

		// --- INITIALIZE THE SPEED ---
		// When homing starts, set the current speed to the initial speed.
		CurrentHomingSpeed = InitialHomingSpeed;

		UE_LOG(LogTemp, Log, TEXT("XP Shard is now homing to player."));
	}

}

void APRPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// --- ADD THIS LOG ---
	UE_LOG(LogTemp, Log, TEXT("PickupBase Tick is running for %s..."), *GetName());

	// If we have a target, move towards it.
	if (HomingTarget)
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

		// --- 3. CHECK FOR ARRIVAL ---
		const float DistanceToTarget = FVector::DistSquared(CurrentLocation, TargetLocation);
		// Check against a squared distance to avoid expensive Sqrt calculation
		if (DistanceToTarget < FMath::Square(100.f))
		{
			// Call the overridable function
			OnCollected();
			Destroy();

			// Destroy self
			Destroy();
		}
	}
}

