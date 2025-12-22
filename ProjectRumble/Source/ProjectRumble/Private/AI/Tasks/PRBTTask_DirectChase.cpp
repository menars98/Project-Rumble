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

	float HoverOffset = 60.0f; // How high above the ground should they fly? (cm)

	// Even if the enemy is above, it will turn its nose down and descend because the target point is below.
	TargetLoc.Z += HoverOffset;

	FVector Direction = (TargetLoc - MyLoc);
	//float Distance = Direction.Size(); // We won't stop just because of the distance anymore!

	float DistanceSq = FVector::DistSquared(MyLoc, TargetLoc);

	// 3. MOVEMENT (Keep Pushing)
	// REMOVING the AcceptanceRadius control. 
	// Keep pushing until it enters the enemy player.
	// The physics engine (Collision) will already prevent it from entering the player.
	FVector NormalizedDir = Direction.GetSafeNormal();
	Pawn->AddMovementInput(NormalizedDir, 1.0f);

	// 4. Rotation
	FRotator CurrentRot = Pawn->GetActorRotation();
	FRotator TargetRot = NormalizedDir.Rotation();
	FRotator NewRot = FMath::RInterpTo(CurrentRot, TargetRot, DeltaSeconds, 10.0f);
	Pawn->SetActorRotation(NewRot);

	// Debug Line
	 DrawDebugLine(GetWorld(), MyLoc, TargetLoc, FColor::Red, false, -1.0f, 0, 2.0f);

}