// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/PRBTTask_DirectChase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"

UPRBTTask_DirectChase::UPRBTTask_DirectChase()
{
	NodeName = "Direct Chase (Flying)";
	bNotifyTick = true; // We need Tick to update movement every frame
}

EBTNodeResult::Type UPRBTTask_DirectChase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UPRBTTask_DirectChase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* AIC = OwnerComp.GetAIOwner();
	APawn* Pawn = AIC ? AIC->GetPawn() : nullptr;

	if (!Pawn)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// Get Target
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (!TargetActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	// Calculate Direction
	FVector MyLoc = Pawn->GetActorLocation();
	FVector TargetLoc = TargetActor->GetActorLocation();
	float DistanceSq = FVector::DistSquared(MyLoc, TargetLoc);

	// Check if reached
	if (DistanceSq <= (AcceptanceRadius * AcceptanceRadius))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	// Move Directly
	FVector Direction = (TargetLoc - MyLoc).GetSafeNormal();
	Pawn->AddMovementInput(Direction, 1.0f);

	// Face Target
	FRotator TargetRot = Direction.Rotation();
	Pawn->SetActorRotation(FMath::RInterpTo(Pawn->GetActorRotation(), TargetRot, DeltaSeconds, 10.0f));
}