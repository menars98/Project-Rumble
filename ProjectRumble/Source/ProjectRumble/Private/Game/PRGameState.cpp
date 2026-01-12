// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PRGameState.h"
#include "Net/UnrealNetwork.h"

APRGameState::APRGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the ActiveDifficultyMultiplier to all clients.
	DOREPLIFETIME(APRGameState, ActiveDifficultyMultiplier);
	DOREPLIFETIME(APRGameState, ServerGameTime);
	DOREPLIFETIME(APRGameState, MatchDuration);
	DOREPLIFETIME(APRGameState, bIsGameActive);

}

void APRGameState::SetActiveDifficultyMultiplier(float NewMultiplier)
{
	// This function must only be called on the server.
	if (HasAuthority())
	{
		ActiveDifficultyMultiplier = NewMultiplier;
	}
}

void APRGameState::SetMatchDuration(float InDuration)
{
	if (HasAuthority())
	{
		MatchDuration = InDuration;
	}
}

void APRGameState::StartGameTimer()
{
	if (HasAuthority())
	{
		bIsGameActive = true;

		OnGameStarted.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("GameState: GAME STARTED! Broadcast sent."));
	}
}

void APRGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If game is active & we have authority, increment the server game time.
	if (HasAuthority() && bIsGameActive)
	{
		ServerGameTime += DeltaTime;
	}
}
