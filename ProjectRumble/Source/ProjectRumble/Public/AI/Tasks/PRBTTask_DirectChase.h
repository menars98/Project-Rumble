// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PRBTTask_DirectChase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API UPRBTTask_DirectChase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPRBTTask_DirectChase();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "AI")
	float AcceptanceRadius = 100.0f;
};
