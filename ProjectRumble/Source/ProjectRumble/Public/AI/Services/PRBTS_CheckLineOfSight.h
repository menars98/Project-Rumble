// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PRBTS_CheckLineOfSight.generated.h"

/**
 * Periodically checks line of sight to the Target Actor.
 * Used to switch between cheap Direct Chase and expensive Pathfinding.
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTS_CheckLineOfSight : public UBTService
{
	GENERATED_BODY()
	
public:
	UPRBTS_CheckLineOfSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// The target we want to see (Player)
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	// The boolean key to update (e.g., "HasLineOfSight")
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector LosKey;

	// Which collision channel blocks sight? (Default: Visibility or WorldStatic)
	UPROPERTY(EditAnywhere, Category = "AI")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_WorldStatic;
};
