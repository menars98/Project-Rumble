// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PRBTS_CheckLineOfSight.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

UPRBTS_CheckLineOfSight::UPRBTS_CheckLineOfSight()
{
	NodeName = "Check Line Of Sight";

	// CRITICAL FOR PERFORMANCE:
	// Don't tick every frame. Tick every 0.5 to 0.7 seconds randomly.
	// For 1000 units, this spreads the load significantly.
	Interval = 0.5f;
	RandomDeviation = 0.2f;
}

void UPRBTS_CheckLineOfSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return;

	AAIController* AIC = OwnerComp.GetAIOwner();
	APawn* MyPawn = AIC ? AIC->GetPawn() : nullptr;
	AActor* TargetActor = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (MyPawn && TargetActor)
	{
		FVector Start = MyPawn->GetActorLocation();
		FVector End = TargetActor->GetActorLocation();

		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(MyPawn);
		Params.AddIgnoredActor(TargetActor); // Ignore target (we want to hit OBSTACLES, not the target)

		// Perform Line Trace
		// We only care if we hit WORLD STATIC objects (Walls, Ground).
		// We do NOT care about other enemies (Pawn). Flying through them is handled by RVO/Braking.
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			TraceChannel,
			Params
		);

		// If we hit something, it means blocked (False). If no hit, path is clear (True).
		bool bHasLineOfSight = !bHit;

		BB->SetValueAsBool(LosKey.SelectedKeyName, bHasLineOfSight);
	}
	else
	{
		// Default to false if target is lost
		BB->SetValueAsBool(LosKey.SelectedKeyName, false);
	}
}