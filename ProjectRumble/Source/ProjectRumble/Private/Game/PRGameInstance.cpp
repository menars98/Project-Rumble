// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PRGameInstance.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Datas/Audio/PRAudioConfig.h"
#include "Game/PRMusicSubsystem.h"

void UPRGameInstance::Init()
{
	Super::Init();

	// 1. Get the Online Subsystem (Steam, EOS, or Null/LAN)
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			// 2. (Callback)
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPRGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPRGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPRGameInstance::OnJoinSessionComplete);

			UE_LOG(LogTemp, Log, TEXT("Found Online Subsystem: %s"), *Subsystem->GetSubsystemName().ToString());
		}
	}

	// Link the config to the subsystem once at game start
	if (UPRMusicSubsystem* MusicSubsystem = GetSubsystem<UPRMusicSubsystem>())
	{
		MusicSubsystem->InitializeConfig(AudioConfig);
		MusicSubsystem->LoadAndApplySettings();
	}
}

void UPRGameInstance::HostGame(int32 MaxPlayers, bool bIsLAN)
{
	if (!SessionInterface.IsValid()) return;

	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession != nullptr)
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}

	// Ayarlarý Yap
	FOnlineSessionSettings SessionSettings{};
	SessionSettings.bIsLANMatch = bIsLAN; // FALSE for Steam, TRUE for Test
	SessionSettings.NumPublicConnections = MaxPlayers;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true; // Requirements for Steam Lobbies
	SessionSettings.bUseLobbiesIfAvailable = true; // For EOS/Steam

	FString MapPath = LobbyMap.GetLongPackageName();
	if (MapPath.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Lobby Map is NOT set in BP_GameInstance!"));
		return;
	}
	// Set Lobby Map (Clients will come here)
	// This “Set” operation is important; Steam reads it.
	SessionSettings.Set(SETTING_MAPNAME, MapPath, EOnlineDataAdvertisementType::ViaOnlineService);

	SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
}

void UPRGameInstance::FindGames(bool bIsLAN)
{
	if (!SessionInterface.IsValid()) return;

	// 1. Create Session Search Object
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	// Lan or Online?
	SessionSearch->bIsLanQuery = bIsLAN;

	// Max server
	SessionSearch->MaxSearchResults = 10000;

	// Find only sessions with presence (Steam requirement)
	SessionSearch->QuerySettings.Set(FName("PRESENCESEARCH"), true, EOnlineComparisonOp::Equals);

	UE_LOG(LogTemp, Log, TEXT("Starting Session Search..."));

	// 2. Start the search
	// When complete, it will call OnFindSessionsComplete
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UPRGameInstance::JoinGame(const FBlueprintSessionResult& SessionToJoin)
{
	if (!SessionInterface.IsValid()) return;

	if (!SessionToJoin.OnlineResult.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot join game: Session Result is invalid."));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Joining Session: %s"), *SessionToJoin.OnlineResult.GetSessionIdStr());

	// Start joining
	SessionInterface->JoinSession(0, NAME_GameSession, SessionToJoin.OnlineResult);
}

void UPRGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session Created! Traveling to Lobby..."));

		// Go to lobby with ServerTravel
		UWorld* World = GetWorld();
		if (World)
		{
			FString MapPath = LobbyMap.GetLongPackageName();
			if (!MapPath.IsEmpty())
			{
				FString TravelURL = FString::Printf(TEXT("%s?listen"), *MapPath);
				World->ServerTravel(TravelURL);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create session."));
	}
}

void UPRGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Session Search Completed. Success: %d"), bWasSuccessful);

	TArray<FBlueprintSessionResult> BlueprintResults;

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		// C++ to Blueprint
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			FBlueprintSessionResult BPResult;
			BPResult.OnlineResult = Result;
			BlueprintResults.Add(BPResult);
		}
	}

	OnServerListUpdated.Broadcast(BlueprintResults);
}

void UPRGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		// 1. Take IP
		FString ConnectString;
		if (SessionInterface->GetResolvedConnectString(NAME_GameSession, ConnectString))
		{
			UE_LOG(LogTemp, Log, TEXT("Join Success! Traveling to: %s"), *ConnectString);

			// 2. (Client Travel)
			if (APlayerController* PC = GetFirstLocalPlayerController())
			{
				PC->ClientTravel(ConnectString, ETravelType::TRAVEL_Absolute);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Join Session Failed."));
	}
}