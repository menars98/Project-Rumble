// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "PRBTS_StuckMonitor.generated.h"

/**
 * Checks if the AI has moved significantly in the last interval.
 * If not, it assumes the AI is stuck and enables Pathfinding.
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTS_StuckMonitor : public UBTService
{
	GENERATED_BODY()
	

public:
	UPRBTS_StuckMonitor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// Blackboard Key to set (e.g., "UsePathfinding")
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector UsePathfindingKey;

	// How far must the AI move to be considered "Not Stuck"?
	UPROPERTY(EditAnywhere, Category = "AI")
	float MovementThreshold = 50.0f;

	// If stuck, how long (seconds) should we force Pathfinding before checking again?
	UPROPERTY(EditAnywhere, Category = "AI")
	float PathfindingCooldown = 4.0f;

private:
	// Helper struct to store state per AI instance
	struct FStuckMonitorMemory
	{
		FVector LastLocation;
		float TimeSinceLastCheck;
		float UnstuckTimer; // How long to keep pathfinding active
	};

	virtual uint16 GetInstanceMemorySize() const override { return sizeof(FStuckMonitorMemory); }
};
