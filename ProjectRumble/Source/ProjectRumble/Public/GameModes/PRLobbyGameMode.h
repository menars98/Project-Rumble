
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PRLobbyGameMode.generated.h"

/**
 * A lightweight GameMode specifically for the Lobby level.
 * Handles player connections, ready checks, and transitioning to the gameplay map.
 */
UCLASS()
class PROJECTRUMBLE_API APRLobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:


	/**
	* Starts the game by traveling to the selected map.
	* @param MapPathOverride Optional: Pass a specific map path. If empty, uses the default.
	*/
	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void StartGame(FString MapPathOverride = "");

	/** Checks if all connected players have set bIsReady to true. */
	UFUNCTION(BlueprintPure, Category = "Lobby")
	bool AreAllPlayersReady() const;

protected:
	/** The map to travel to when the game starts. */
	UPROPERTY(EditDefaultsOnly, Category = "Lobby")
	TSoftObjectPtr<UWorld> GameplayMap;

	// Called when a player successfully logs in.
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Called when a player leaves.
	virtual void Logout(AController* Exiting) override;
};
