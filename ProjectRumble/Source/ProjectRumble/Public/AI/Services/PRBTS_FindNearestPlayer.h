// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PRBTS_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTS_FindNearestPlayer : public UBTService
{
	GENERATED_BODY()
	
public:

	UPRBTS_FindNearestPlayer();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Blackboard Key to set (TargetActor)
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
};
