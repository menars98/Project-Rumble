// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRXpShard.generated.h"

class APRCharacterBase;

UCLASS()
class PROJECTRUMBLE_API APRXpShard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRXpShard();

	// The amount of XP this shard grants.
	// BlueprintReadWrite allows Blueprints to read and change this value.
	// ExposeOnSpawn makes it an input pin on the "Spawn Actor" node.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot", meta = (ExposeOnSpawn = "true"))
	float XPValue;

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Loot")
	bool bIsBeingPulled;

	/** Starts the homing process towards a target character. */
	void StartHoming(APRCharacterBase* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// The character this shard is currently moving towards.
	UPROPERTY()
	TObjectPtr<APRCharacterBase> HomingTarget;

	// The speed at which the shard moves towards the target.
	UPROPERTY(EditAnywhere, Category = "Movement")
	float HomingSpeed = 1500.f;
};
