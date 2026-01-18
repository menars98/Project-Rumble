// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PRBTS_StuckMonitor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"

UPRBTS_StuckMonitor::UPRBTS_StuckMonitor()
{
	NodeName = "Monitor Stuck State";
	Interval = 1.0f;        // Check every 1 second
	RandomDeviation = 0.2f; // Slight randomness
	bNotifyBecomeRelevant = true; // To initialize location
}

void UPRBTS_StuckMonitor::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	FStuckMonitorMemory* MyMemory = (FStuckMonitorMemory*)NodeMemory;

	if (Pawn && MyMemory)
	{
		MyMemory->LastLocation = Pawn->GetActorLocation();
		MyMemory->UnstuckTimer = 0.0f;
	}
}

void UPRBTS_StuckMonitor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	FStuckMonitorMemory* MyMemory = (FStuckMonitorMemory*)NodeMemory;
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();

	if (!Pawn || !MyMemory || !BB) return;

	// 1. If we are currently in "Forced Pathfinding Mode" (Cooldown)
	if (MyMemory->UnstuckTimer > 0.0f)
	{
		// Count down
		MyMemory->UnstuckTimer -= Interval; // Approximate since TickNode runs on Interval

		// Still keep pathfinding true
		BB->SetValueAsBool(UsePathfindingKey.SelectedKeyName, true);

		// Update location so we don't trigger stuck immediately after cooldown ends
		MyMemory->LastLocation = Pawn->GetActorLocation();
		return;
	}

	// 2. Check Distance Moved
	float DistSq = FVector::DistSquared(MyMemory->LastLocation, Pawn->GetActorLocation());
	float ThresholdSq = MovementThreshold * MovementThreshold;

	bool bIsStuck = (DistSq < ThresholdSq);

	if (bIsStuck)
	{
		// We are stuck! Activate Pathfinding and start cooldown timer.
		BB->SetValueAsBool(UsePathfindingKey.SelectedKeyName, true);
		MyMemory->UnstuckTimer = PathfindingCooldown; // Keep pathfinding for X seconds

		// UE_LOG(LogTemp, Warning, TEXT("AI %s is STUCK! Switching to Pathfinding."), *Pawn->GetName());
	}
	else
	{
		// We are moving fine. Use cheap Direct Chase.
		BB->SetValueAsBool(UsePathfindingKey.SelectedKeyName, false);
	}

	// Update Last Location for the next check
	MyMemory->LastLocation = Pawn->GetActorLocation();
}