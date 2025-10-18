// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PRAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"


APRAIController::APRAIController()
{
}

void APRAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
