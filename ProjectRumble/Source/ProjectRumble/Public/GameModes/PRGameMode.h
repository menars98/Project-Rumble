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

protected:
	// --- DIFFICULTY MANAGEMENT ---
	/**
	 * Recalculates the highest Difficulty Stat value among all players and updates ActiveDifficultyMultiplier.
	 * Called only when a player's Difficulty stat changes.
	 */
	void RecalculateActiveDifficulty();

	// Function to bind to a player's stats component delegate.
	void BindToPlayerDifficulty(UPRStatsComponent* PlayerStatsComp);

	/**
	 * Callback function executed when any bound player's Difficulty stat changes.
	 * Because the Difficulty stat changed, we must recalculate the highest active multiplier.
	 */
	UFUNCTION()
	void OnPlayerDifficultyChanged(float NewDifficultyValue);

	// --- LIFECYCLE ---
	virtual void BeginPlay() override;

	// Override the PlayerState spawn to ensure we bind to new players immediately.
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
