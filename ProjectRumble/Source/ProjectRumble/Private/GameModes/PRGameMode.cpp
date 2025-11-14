// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PRGameMode.h"
#include "Player/PRPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include <Game/PRGameState.h>

APRGameMode::APRGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APRGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Bind to all currently existing players (important for PIE testing or initial load).
	TArray<AActor*> PlayerStates;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRPlayerState::StaticClass(), PlayerStates);

	for (AActor* PlayerStateActor : PlayerStates)
	{
		if (APRPlayerState* PR_PlayerState = Cast<APRPlayerState>(PlayerStateActor))
		{
			// Bind to the StatsComponent's Difficulty Delegate.
			BindToPlayerDifficulty(PR_PlayerState->StatsComponent);
		}
	}
	
	// Set the initial difficulty based on all players.
	RecalculateActiveDifficulty();
}

void APRGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// New player joined: Ensure we bind to their stats component.
	if (APRPlayerState* PR_PlayerState = NewPlayer->GetPlayerState<APRPlayerState>())
	{
		BindToPlayerDifficulty(PR_PlayerState->StatsComponent);
	}
}
void APRGameMode::OnPlayerDifficultyChanged(float NewDifficultyValue)
{
	// A stat has changed on one player, so we must find the highest difficulty among ALL players.
	RecalculateActiveDifficulty();
}

void APRGameMode::RecalculateActiveDifficulty()
{
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
				HighestDifficulty = FMath::Max(HighestDifficulty, PlayerDifficulty);
			}
		}
	}

	// --- 2. UPDATE THE GAME STATE ---

	// Get a reference to our custom GameState.
	if (APRGameState* PR_GameState = GetGameState<APRGameState>())
	{
		// Set the value on the GameState. The GameState will handle replicating this to clients.
		PR_GameState->SetActiveDifficultyMultiplier(HighestDifficulty);
	}
}

void APRGameMode::BindToPlayerDifficulty(UPRStatsComponent* PlayerStatsComp)
{
	if (PlayerStatsComp)
	{
		// 1. Bind the function to the player's difficulty change delegate.
		PlayerStatsComp->OnDifficultyChangedDelegate.AddDynamic(this, &APRGameMode::OnPlayerDifficultyChanged);

		// 2. Set the initial difficulty based on the new player's current stat.
		// This handles the initial state after binding.
		OnPlayerDifficultyChanged(PlayerStatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Difficulty));
	}
}




