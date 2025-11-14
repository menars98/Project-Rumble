// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PRGameState.h"
#include "Net/UnrealNetwork.h"

void APRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate the ActiveDifficultyMultiplier to all clients.
	DOREPLIFETIME(APRGameState, ActiveDifficultyMultiplier);
}

void APRGameState::SetActiveDifficultyMultiplier(float NewMultiplier)
{
	// This function must only be called on the server.
	if (HasAuthority())
	{
		ActiveDifficultyMultiplier = NewMultiplier;
	}
}