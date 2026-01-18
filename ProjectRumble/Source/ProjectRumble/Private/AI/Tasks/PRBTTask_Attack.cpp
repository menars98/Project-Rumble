// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/PRBTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PRAIBase.h"

UPRBTTask_Attack::UPRBTTask_Attack()
{
	NodeName = "Perform Attack";
}

EBTNodeResult::Type UPRBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	APRAIBase* AIPawn = AIC ? Cast<APRAIBase>(AIC->GetPawn()) : nullptr;

	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	// Get the target to aim at
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));

	// Call the attack function on the AI Character
	AIPawn->PerformAttack(Target);

	// Return Succeeded immediately. 
	// The Behavior Tree's "Wait" node will handle the attack rate/cooldown.
	return EBTNodeResult::Succeeded;
}
