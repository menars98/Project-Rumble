// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRPickupBase.generated.h"

class APRCharacterBase;
class UPRLootComponent;

UCLASS()
class PROJECTRUMBLE_API APRPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRPickupBase();
	/** Starts the homing process towards a target character. */
	void StartHoming(APRCharacterBase* Target);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup|Movement")
	bool bStartHomingOnSpawn = false;

	// The generic value this pickup holds (e.g., amount of XP, Gold, Health).
	// Set by the LootComponent when spawned.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated, Category = "Rumble | Pickup")
	float Value;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/**
	 * The core logic that executes when the pickup is collected.
	 * This is meant to be overridden by child classes (XpShard, GoldPickup).
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Rumble | Pickup")
	void OnCollected();
	virtual void OnCollected_Implementation(); // C++ implementation for the above

	// The character this shard is currently moving towards.
	UPROPERTY(ReplicatedUsing = OnRep_HomingTarget)
	TObjectPtr<APRCharacterBase> HomingTarget;

	// The speed at which the shard STARTS moving towards the target.
	UPROPERTY(EditAnywhere, Category = "Rumble | Pickup | Movement", meta = (ClampMin = "0.1"))
	float InitialHomingSpeed = 300.0f;

	// The MAXIMUM speed the shard can reach.
	UPROPERTY(EditAnywhere, Category = "Rumble | Pickup | Movement", meta = (ClampMin = "0.1"))
	float MaxHomingSpeed = 3000.f;

	// How quickly the shard accelerates to its max speed (higher = faster acceleration).
	UPROPERTY(EditAnywhere, Category = "Rumble | Pickup | Movement")
	float HomingAcceleration = 2.0f;

	// The current speed of the shard. This will increase over time.
	float CurrentHomingSpeed;

	// A flag to prevent StartHoming from being called multiple times.
	bool bIsHoming = false;

	UFUNCTION()
	void OnRep_HomingTarget();
};
