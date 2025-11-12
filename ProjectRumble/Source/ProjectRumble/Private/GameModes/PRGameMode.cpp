// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PRGameMode.h"
#include "Player/PRPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PRStatsComponent.h"

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
	float HighestDifficulty = 1.0f; // Minimum multiplier is 1.0 (100%)
	TArray<AActor*> PlayerStates;

	// 1. Find all active player states in the world (handles co-op).
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRPlayerState::StaticClass(), PlayerStates);

	for (AActor* PlayerStateActor : PlayerStates)
	{
		if (APRPlayerState* PR_PlayerState = Cast<APRPlayerState>(PlayerStateActor))
		{
			if (UPRStatsComponent* StatsComp = PR_PlayerState->StatsComponent)
			{
				// Get the Difficulty Stat value.
				float PlayerDifficulty = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Difficulty);

				// 2. Find the highest value across all players.
				HighestDifficulty = FMath::Max(HighestDifficulty, PlayerDifficulty);
			}
		}
	}

	// 3. Update the global multiplier only if it has actually changed (for consistency).
	if (!FMath::IsNearlyEqual(ActiveDifficultyMultiplier, HighestDifficulty))
	{
		ActiveDifficultyMultiplier = HighestDifficulty;
		// @TODO: Add an Event Dispatcher here if other systems need to react immediately (e.g., UI updates).
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




