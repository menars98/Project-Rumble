// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PRGameState.generated.h"



UCLASS()
class PROJECTRUMBLE_API APRGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	APRGameState();

	virtual void Tick(float DeltaTime) override;

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

	// --- GAME TIME ---
	UFUNCTION(BlueprintPure, Category = "Game|Time")
	float GetServerGameTime() const { return ServerGameTime; }

protected:
	/** The current active difficulty multiplier for the game, replicated to all clients. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Difficulty")
	float ActiveDifficultyMultiplier = 1.0f;

	// The current game duration, calculated by the server and replicated to clients.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Game|Time")
	float ServerGameTime = 0.0f;

	bool bIsGameActive = false;

public:

	void StartGameTimer() { bIsGameActive = true; }
};
