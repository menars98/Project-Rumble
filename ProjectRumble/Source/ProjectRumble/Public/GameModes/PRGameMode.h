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

	// The maximum multiplier that the Difficulty stat can provide.
	// e.g., 6.0f means a 6x increase at 600% Difficulty or higher.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game|Difficulty")
	float MaxDifficultyMultiplier = 6.0f;

protected:
	// --- DIFFICULTY MANAGEMENT ---
	/**
	 * Recalculates the highest Difficulty Stat value among all players and updates ActiveDifficultyMultiplier.
	 * Called only when a player's Difficulty stat changes.
	 */
	UFUNCTION()
	void RecalculateActiveDifficulty();

	// Function to bind to a player's stats component delegate.
	UFUNCTION()
	void BindToPlayerDifficulty(UPRStatsComponent* PlayerStatsComp);

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

};
