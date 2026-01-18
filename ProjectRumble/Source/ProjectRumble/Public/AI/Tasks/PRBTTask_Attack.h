// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PRBTTask_Attack.generated.h"

/**
 * Task to trigger the AI's attack function.
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPRBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
};
