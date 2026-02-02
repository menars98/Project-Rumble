// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PRLobbyGameMode.h"
#include "Player/PRPlayerState.h"
#include "GameFramework/GameState.h"
#include "Player/PRPlayerController.h"

void APRLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// Logic to update UI when someone joins could go here.
	// For now, we just let the PlayerState replicate and the UI will pick it up.

	if (APRPlayerController* PC = Cast<APRPlayerController>(NewPlayer))
	{
		// Tell the client to play the Lobby music
		PC->Client_UpdateLevelMusic(LevelMusic);
	}
}

void APRLobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	// Logic to update UI when someone leaves.
}

bool APRLobbyGameMode::AreAllPlayersReady() const
{
	if (!GameState) return false;

	// If there are no players, we can't be ready.
	if (GameState->PlayerArray.Num() == 0) return false;

	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (APRPlayerState* RumblePS = Cast<APRPlayerState>(PS))
		{
			if (!RumblePS->GetIsReady())
			{
				return false; // Found someone who isn't ready.
			}
		}
	}

	// Everyone is ready!
	return true;
}

void APRLobbyGameMode::StartGame(FString MapPathOverride)
{
	UWorld* World = GetWorld();
	if (!World) return;

	bUseSeamlessTravel = true;

	// 1. Which map to travel to?
	FString TargetMapPath;

	if (!MapPathOverride.IsEmpty())
	{
		TargetMapPath = MapPathOverride;
	}
	else
	{
		// GetLongPackageName() can give us: "/Game/Rumble/Maps/PrototypeMap" 
		TargetMapPath = GameplayMap.GetLongPackageName();
	}

	if (TargetMapPath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("StartGame Failed: No GameplayMap selected in BP_LobbyGameMode!"));
		return;
	}

	// 2. Server Travel
	FString TravelURL = FString::Printf(TEXT("%s?listen"), *TargetMapPath);

	UE_LOG(LogTemp, Log, TEXT("Lobby: Starting Game. Traveling to: %s"), *TravelURL);
	World->ServerTravel(TravelURL);
}
