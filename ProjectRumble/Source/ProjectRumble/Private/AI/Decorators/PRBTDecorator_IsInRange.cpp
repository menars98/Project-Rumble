// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/PRBTDecorator_IsInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PRAIBase.h"
#include "AIController.h"

UPRBTDecorator_IsInRange::UPRBTDecorator_IsInRange()
{
	NodeName = "Is In Attack Range";

	bNotifyTick = true;

}

void UPRBTDecorator_IsInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	bool bIsInRange = CalculateRawConditionValue(OwnerComp, NodeMemory);

	// 2. If we are in Range (True) AND this branch is not currently active (i.e., if it is in Chase):
	// Force the tree to move to this branch (Attack) by calling “RequestExecution”.
	if (bIsInRange)
	{
		// Note: This function does nothing if this branch is already running.
		// But if the right branch (Chase) is running, it ABORTS it and jumps here.
		OwnerComp.RequestExecution(this);
	}
}

bool UPRBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// 1. Get the AI Controller and the Controlled Pawn
	AAIController* AIC = OwnerComp.GetAIOwner();
	APRAIBase* AIPawn = AIC ? Cast<APRAIBase>(AIC->GetPawn()) : nullptr;

	if (!AIPawn)
	{
		return false;
	}

	// 2. Get the Target Actor from Blackboard
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (!TargetActor)
	{
		return false; // No target implies not in range
	}

	// 3. Get the dynamic Attack Range from the AI's stats
	float AttackRange = AIPawn->GetAttackRange();

	// 4. Calculate Distance Squared (Optimization: Avoid Sqrt)
	float DistanceSq = FVector::DistSquared(AIPawn->GetActorLocation(), TargetActor->GetActorLocation());

	// Add error margin to the check distance
	float CheckDistance = AttackRange + ErrorMargin;

	// Compare squared distances
	return DistanceSq <= (CheckDistance * CheckDistance);
}