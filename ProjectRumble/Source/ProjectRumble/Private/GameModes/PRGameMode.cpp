// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PRGameMode.h"
#include "Player/PRPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include "Game/PRGameState.h"
#include "AI/PRAIBase.h"
#include <Managers/PRSpawnerManager.h>

APRGameMode::APRGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APRGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APRGameMode::StartPlay()
{
	Super::StartPlay();

	if (SpawnerManagerClass)
	{
		GetWorld()->SpawnActor<APRSpawnerManager>(SpawnerManagerClass);
		UE_LOG(LogTemp, Log, TEXT("Spawner Manager has been initialized by GameMode."));
	}
}

void APRGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// This is the SAFEST place to handle new player setup.
	if (NewPlayer)
	{
		if (APRPlayerState* PR_PlayerState = NewPlayer->GetPlayerState<APRPlayerState>())
		{
			// The PlayerState is guaranteed to exist here.
			// Now we wait for its internal components to be ready.
			PR_PlayerState->OnStatsComponentReady.AddDynamic(this, &APRGameMode::HandlePlayerReady);
		}

		if (NewPlayer->GetPawn() == nullptr)
		{
			RestartPlayer(NewPlayer); 
			UE_LOG(LogTemp, Warning, TEXT("[SERVER] Late joiner %s forced to spawn."), *NewPlayer->GetName());
		}

	}
}

void APRGameMode::HandlePlayerReady(UPRStatsComponent* PlayerStatsComp)
{
	if (PlayerStatsComp)
	{
		// 1. Bind to the difficulty change delegate.
		PlayerStatsComp->OnDifficultyChangedDelegate.AddDynamic(this, &APRGameMode::OnPlayerDifficultyChanged);

		// 2. A player is now fully ready, so we recalculate the game's difficulty.
		RecalculateActiveDifficulty();
	}
}

void APRGameMode::OnPlayerDifficultyChanged(float NewDifficultyValue)
{
	// A stat has changed on one player, so we must find the highest difficulty among ALL players.
	RecalculateActiveDifficulty();
}

void APRGameMode::RecalculateActiveDifficulty()
{
	// --- GUARD CLAUSE: Ensure GameState is valid before proceeding ---
	APRGameState* PR_GameState = GetGameState<APRGameState>();
	if (!PR_GameState)
	{
		return;
	}

	// 1. FIND THE HIGHEST DIFFICULTY BONUS
	float HighestDifficulty = 1.0f;

	TArray<AActor*> PlayerStates;
	// 1. Find all active player states in the world (handles co-op).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRPlayerState::StaticClass(), PlayerStates);

	for (AActor* PlayerStateActor : PlayerStates)
	{
		if (APRPlayerState* PR_PlayerState = Cast<APRPlayerState>(PlayerStateActor))
		{
			if (UPRStatsComponent* StatsComp = PR_PlayerState->StatsComponent)
			{
				float PlayerDifficulty = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Difficulty);
				// Keep track of the highest value found among all players.
				HighestDifficulty = FMath::Max(HighestDifficulty, PlayerDifficulty);

			}
		}
	}

	// --- 2. UPDATE THE GAME STATE ---
	// Apply the hard cap defined in the GameMode's properties.
	float FinalMultiplier = FMath::Min(HighestDifficulty, MaxDifficultyMultiplier);


	// Only proceed if the value has actually changed.
	if (!FMath::IsNearlyEqual(PR_GameState->GetActiveDifficultyMultiplier(), FinalMultiplier))
	{
		// Set the value on the GameState. The GameState will handle replicating this to clients.
		PR_GameState->SetActiveDifficultyMultiplier(FinalMultiplier);

		// Update all existing AI actors in the world with the new multiplier.
		TArray<AActor*> FoundAIs;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRAIBase::StaticClass(), FoundAIs);

		for (AActor* AIActor : FoundAIs)
		{
			if (APRAIBase* AI = Cast<APRAIBase>(AIActor))
			{
				// Call the function on each AI to re-initialize its stats with the new multiplier.
				AI->UpdateDifficultyMultiplier(FinalMultiplier);
			}
		}
		// Log the change for debugging.
		UE_LOG(LogTemp, Log, TEXT("Active Difficulty Multiplier updated to: %.2f"), FinalMultiplier);
	}
	
}




