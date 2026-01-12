// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PRGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStartedSignature);

UCLASS()
class PROJECTRUMBLE_API APRGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	APRGameState();

	virtual void Tick(float DeltaTime) override;

	// This function is required for replication.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable, Category = "Game|Events")
	FOnGameStartedSignature OnGameStarted;

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

	// Getter for the match duration
	UFUNCTION(BlueprintPure, Category = "Game|Time")
	float GetMatchDuration() const { return MatchDuration; }

	UFUNCTION(BlueprintPure, Category = "Game|State")
	bool IsGameActive() const { return bIsGameActive; }

	// Server only setter
	void SetMatchDuration(float InDuration);

protected:
	/** The current active difficulty multiplier for the game, replicated to all clients. */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Difficulty")
	float ActiveDifficultyMultiplier = 1.0f;

	// The current game duration, calculated by the server and replicated to clients.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Game|Time")
	float ServerGameTime = 0.0f;

	// The duration of the match in seconds before Endless/Overtime starts.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Game|Time")
	float MatchDuration = 600.0f; // Default 10 mins if not set

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Replicated, Category = "Game|State")
	bool bIsGameActive = false;

public:

	void StartGameTimer();
};
