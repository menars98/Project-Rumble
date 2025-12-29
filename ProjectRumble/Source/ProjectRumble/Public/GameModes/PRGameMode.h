// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PRGameMode.generated.h"

class UPRStatsComponent;

UCLASS()
class PROJECTRUMBLE_API APRGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	APRGameMode();

	virtual void Tick(float DeltaSeconds) override;

	// The maximum multiplier that the Difficulty stat can provide.
	// e.g., 6.0f means a 6x increase at 600% Difficulty or higher.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game|Difficulty")
	float MaxDifficultyMultiplier = 6.0f;

	/**
	 * Called by a PlayerController when it opens the Level Up UI.
	 * Pauses the game and increments the lock counter.
	 */
	void RegisterPlayerInMenu();

	/**
	 * Called by a PlayerController when it finishes selection (ApplyReward).
	 * Decrements the counter and unpauses ONLY if no one else is in the menu.
	 */
	void UnregisterPlayerInMenu();

	virtual void Logout(AController* Exiting) override;

	/** Checks if all players are dead. If so, triggers Game Over. */
	void CheckPlayerDeaths();

	// Getter for the Spawner Manager to access
	UFUNCTION(BlueprintPure, Category = "Game|Config")
	class UPRSpawnConfig* GetLevelSpawnConfig() const { return LevelSpawnConfig; }
protected:

	/**
	* The Spawn Configuration for the current level (Timeline, Enemies, Biome).
	* Assign "DA_ForestConfig" here in BP_GameMode_Forest.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble|Game|Config")
	TObjectPtr<class UPRSpawnConfig> LevelSpawnConfig;

	/** The class of the Spawner Manager to spawn at the start of the game. */
	UPROPERTY(EditDefaultsOnly, Category = "Rumble|Game|Spawning")
	TSubclassOf<class APRSpawnerManager> SpawnerManagerClass;

	// A reference to the spawned Spawner Manager instance.
	UPROPERTY()
	TObjectPtr<class APRSpawnerManager> SpawnerManagerInstance;

	// --- DIFFICULTY MANAGEMENT ---
	/**
	 * The currently active Difficulty multiplier based on the highest Difficulty stat among all players.
	 * Used by the Spawner Manager to scale enemy stats and spawn rates.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Rumble|Game|Difficulty")
	float ActiveDifficultyMultiplier = 0.5f;

	/**
	* [CONFIG] The game's duration in seconds.
	* Endless mode starts when this time expires.
	* We did this because we can make another game modes like Fast, Normal and change this value accordingly.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Rumble|Game|Config")
	float MatchDurationInSeconds = 600.0f;

	// How many players are currently looking at the Level Up screen?
	int32 PlayersInLevelUpMenu = 0;
	// --- DIFFICULTY MANAGEMENT ---
	/**
	 * Recalculates the highest Difficulty Stat value among all players and updates ActiveDifficultyMultiplier.
	 * Called only when a player's Difficulty stat changes.
	 */
	UFUNCTION()
	void RecalculateActiveDifficulty();

	/** Called when a PlayerState reports that its StatsComponent is ready. */

	UFUNCTION()
	void HandlePlayerReady(UPRStatsComponent* PlayerStatsComp);
	/**
	 * Callback function executed when any bound player's Difficulty stat changes.
	 * Because the Difficulty stat changed, we must recalculate the highest active multiplier.
	 */
	UFUNCTION()
	void OnPlayerDifficultyChanged(float NewDifficultyValue);

	// --- LIFECYCLE ---
	virtual void BeginPlay() override;

	virtual void StartPlay() override;

	// Override the PlayerState spawn to ensure we bind to new players immediately.
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Triggers the end of the match logic. */
	void GameOver(bool bWon);

};
