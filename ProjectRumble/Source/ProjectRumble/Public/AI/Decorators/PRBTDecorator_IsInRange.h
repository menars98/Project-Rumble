// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "PRBTDecorator_IsInRange.generated.h"

/**
 * Checks if the AI is within its Attack Range (defined in Stats) relative to the Target Actor.
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTDecorator_IsInRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UPRBTDecorator_IsInRange();

protected:
	// Performs the condition check. Returns true if in range, false otherwise.
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// The Blackboard Key storing the Target Actor (Player).
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	// An extra buffer distance. If Range is 800 and ErrorMargin is 50, AI attacks at 850.
	// Useful to prevent flickering behavior at the edge of range.
	UPROPERTY(EditAnywhere, Category = "AI")
	float ErrorMargin = 50.0f;
};
