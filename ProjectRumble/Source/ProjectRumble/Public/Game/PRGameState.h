// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PRGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API APRGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// This function is required for replication.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- DIFFICULTY ---

	/**
	 * Sets the active difficulty multiplier. Should ONLY be called on the server (by the GameMode).
	 * The value will then replicate to all clients.
	 */
	void SetActiveDifficultyMultiplier(float NewMultiplier);

	/** Returns the current replicated difficulty multiplier. Safe to call on clients. */
	UFUNCTION(BlueprintPure, Category = "Game|Difficulty")
	float GetActiveDifficultyMultiplier() const { return ActiveDifficultyMultiplier; }

protected:
	/** The current active difficulty multiplier for the game, replicated to all clients. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Difficulty")
	float ActiveDifficultyMultiplier = 1.0f;

};
