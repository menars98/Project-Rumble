// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h" 
#include "FindSessionsCallbackProxy.h"
#include "PRGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerListUpdated, const TArray<FBlueprintSessionResult>&, SessionResults);

class UDataTable;
class UPRAudioConfig;

UCLASS()
class PROJECTRUMBLE_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	// --- Multiplayer ---
	
	// --- BLUEPRINT CALLABLE FUNCTIONS ---

	/** Starts a session (Host Game). */
	UFUNCTION(BlueprintCallable, Category = "Network")
	void HostGame(int32 MaxPlayers, bool bIsLAN);

	/** Finds available sessions. */
	UFUNCTION(BlueprintCallable, Category = "Network")
	void FindGames(bool bIsLAN);

	/** Joins a found session. */
	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinGame(const FBlueprintSessionResult& SessionToJoin);

	// --- DELEGATES ---
	UPROPERTY(BlueprintAssignable, Category = "Network")
	FOnServerListUpdated OnServerListUpdated;

	/// --- INGAME PROPERTIES ---
	/** The widget class to use for displaying floating damage numbers. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<class UPRWorldUserWidget> DamageNumberWidgetClass;

    /** The Data Table containing definitions for all loot profiles in the game. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<class UDataTable> LootProfileTable;

protected:

	// --- INTERNAL OSS POINTERS ---
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// --- DELEGATES ---
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// --- CONFIG ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Network|Maps")
	TSoftObjectPtr<UWorld> LobbyMap;

	UPROPERTY(EditDefaultsOnly, Category = "PR|Audio")
	TObjectPtr<UPRAudioConfig> AudioConfig;
};
