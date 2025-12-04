// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/PRBTS_FindNearestPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Game/PRGameState.h"
#include "Player/PRPlayerState.h"

UPRBTS_FindNearestPlayer::UPRBTS_FindNearestPlayer()
{
    NodeName = "Find Nearest Player";
    Interval = 0.5f;
	RandomDeviation = 0.1f; // Add slight randomness to avoid synchronization issues
}

void UPRBTS_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!AIPawn) return;

	//Finding players through GameState is a faster way(instead of GetAllActorsOfClass).
	APRGameState* GameState = GetWorld()->GetGameState<APRGameState>();
	if (!GameState) return;

	AActor* ClosestPlayer = nullptr;
	float MinDistanceSq = FLT_MAX; // Infinite
	FVector AILocation = AIPawn->GetActorLocation();

	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (PS && PS->GetPawn())
		{
			APawn* PlayerPawn = PS->GetPawn();

			// Dont target destroyed actors(Maybe add health control)
			if (!PlayerPawn->IsActorBeingDestroyed())
			{
				// Squared distance for performance
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
		FString TargetName = ClosestPlayer->GetName();
		UE_LOG(LogTemp, Warning, TEXT("AI %s selected target: %s"), *AIPawn->GetName(), *TargetName);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestPlayer);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI %s found NO TARGET!"), *AIPawn->GetName());
		OwnerComp.GetBlackboardComponent()->ClearValue(TargetActorKey.SelectedKeyName);
	}
}
