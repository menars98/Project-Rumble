// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PRAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;

UCLASS()
class PROJECTRUMBLE_API APRAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APRAIController();

protected:
	// The Behavior Tree asset to run. Assigned in the derived Blueprint class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	// OnPossess is called when the controller takes control of a pawn.
	virtual void OnPossess(APawn* InPawn) override;

};
