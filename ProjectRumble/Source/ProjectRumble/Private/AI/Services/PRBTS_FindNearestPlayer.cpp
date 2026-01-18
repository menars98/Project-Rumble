// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PRBTS_FindNearestPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Game/PRGameState.h"
#include "Player/PRPlayerState.h"
#include "AI/PRAIBase.h"

UPRBTS_FindNearestPlayer::UPRBTS_FindNearestPlayer()
{
    NodeName = "Find Nearest Player";
    Interval = 0.5f;
	RandomDeviation = 0.1f; // Add slight randomness to avoid synchronization issues
}

void UPRBTS_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APRAIBase* AIPawn = Cast<APRAIBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (!AIPawn) return;

	APRGameState* GameState = GetWorld()->GetGameState<APRGameState>();
	if (!GameState) return;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return;


	AActor* ClosestPlayer = nullptr;
	float MinDistanceSq = FLT_MAX;
	FVector AILocation = AIPawn->GetActorLocation();

	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (PS && PS->GetPawn())
		{
			APawn* PlayerPawn = PS->GetPawn();

			if (!PlayerPawn->IsActorBeingDestroyed()) 
			{
				float DistSq = FVector::DistSquared(AILocation, PlayerPawn->GetActorLocation());

				if (DistSq < MinDistanceSq)
				{
					MinDistanceSq = DistSq; 
					ClosestPlayer = PlayerPawn;
				}
			}
		}
	}

	if (ClosestPlayer)
	{
		UObject* CurrentTarget = BB->GetValueAsObject(TargetActorKey.SelectedKeyName);
		if (CurrentTarget != ClosestPlayer)
		{
			BB->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestPlayer);
			// OwnerComp.RestartTree(); 
		}

		// This is what the DoN "Fly To" task needs.
		BB->SetValueAsVector(TargetLocationKey.SelectedKeyName, ClosestPlayer->GetActorLocation());

		float AttackRange = AIPawn->GetAttackRange();
		float RangeSq = FMath::Square(AttackRange); // + ErrorMargin maybe

		UE_LOG(LogTemp, Warning, TEXT("DistSq: %f, RangeSq: %f"), MinDistanceSq, RangeSq);

		bool bShouldAttack = false;

		if (MinDistanceSq <= RangeSq)
		{
			if (FMath::FRand() <= AttackProbability)
			{
				bShouldAttack = true;
			}
		}

		BB->SetValueAsBool(AttackConditionKey.SelectedKeyName, bShouldAttack);
	}
	else
	{
		BB->ClearValue(TargetActorKey.SelectedKeyName);
		BB->ClearValue(TargetLocationKey.SelectedKeyName);
		BB->SetValueAsBool(AttackConditionKey.SelectedKeyName, false);
	}
}
