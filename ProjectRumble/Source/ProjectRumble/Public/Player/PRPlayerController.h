// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PRPlayerController.generated.h"

class UDataTable;
class UUserWidget;
class UPRUpgradeData;
class UPRItemDefinition;
class UInputAction;
class UPRWorldUserWidget;

UCLASS()
class PROJECTRUMBLE_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;


protected:
	/**
	 * An array of Data Assets that holds all possible ITEMS (Weapons, Tomes, etc.) available in the level up pool.
	 * Assigned in the BP_PlayerController.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRItemDefinition>> AllPossibleLevelUpItems;

	// Array to hold the rewards that are currently being offered to the player.
	// We make it BlueprintReadOnly so the UI can read it.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRUpgradeData>> OfferedRewards;

	// -- DATA TABLES --
	// This is our main STAT definition table.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> StatsInfoDataTable;

	// -- UI --
	// The Level Up screen widget class. Assigned in the BP_PlayerController Blueprint.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LevelUpWidgetClass;

	// The instance of the level up screen, so we can remove it later.
	UPROPERTY()
	TObjectPtr<UUserWidget> LevelUpWidgetInstance;

	// The Inventory screen widget class.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> InventoryScreenWidgetClass;

	// The instance of the inventory screen, so we can check if it's open.
	UPROPERTY()
	TObjectPtr<UUserWidget> InventoryScreenInstance;

	// The Stat screen widget class.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ItemFoundPopupWidgetClass;

	// The instance of the inventory screen, so we can check if it's open.
	UPROPERTY()
	TObjectPtr<UUserWidget> StatScreenInstance;

	// --- PAUSE MENU ---

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenuInstance;

	// -- CORE --

	virtual void OnRep_Pawn() override;
	// Client-side: Called when PlayerState is correctly replicated.
	virtual void OnRep_PlayerState() override;

	// Called when this controller possesses a pawn (character).
	// This is a more reliable place than BeginPlay to bind to player-specific delegates.
	virtual void OnPossess(APawn* InPawn) override;

	// Called by the StatsComponent's OnLevelUpDelegate.
	UFUNCTION()
	void ShowLevelUpScreen(int32 NewLevel);

	virtual void SetupInputComponent() override;

	// -- INPUT --
	// The Input Action for toggling the inventory screen.
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> PauseAction;

	// Called when the ToggleInventoryAction is triggered.
	void ToggleInventoryScreen();

	/** Called locally when the pause input is pressed. Sends a request to the server. */
	void TogglePauseMenu();

	/**
   * [SERVER] Function to request a pause/unpause.
   * The server will validate and then broadcast the change to all clients.
   */
	UFUNCTION(Server, Reliable)
	void Server_RequestTogglePause();

	/**
	 * [CLIENT] Function called by the server on ALL clients to actually show/hide the pause menu.
	 * @param bIsPaused The new pause state of the game.
	 */
	UFUNCTION(Client, Reliable)
	void Client_TogglePause(bool bIsPaused);

	/**
	 * [SERVER] Function to request resuming the game from a paused state.
	 * Called by clients when they close the pause menu.
	 */
	UFUNCTION(Server, Reliable)
	void Server_RequestResumeGame();

public:
	// Called by the UI Widget when a player clicks on a reward button.
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void ApplyReward(UPRUpgradeData* ChosenUpgrade);

	/**
	 * A generic function to request and grant rewards from a specific loot pool.
	 * Can be called by chests, bosses, or any other reward-granting source.
	 * @param LootPool A Data Table containing UUpgradePoolEntry structs that define what can be dropped.
	 * @param NumToOffer The number of rewards to generate and offer.
	 * @param bGrantDirectly If true, grants the first reward immediately. If false, shows the Level Up screen. (For future flexibility)
	 */
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void RequestRewards(UDataTable* LootPool, int32 NumToOffer, bool bGrantDirectly = true);

	// Called by UI widgets when they are closed to resume the game.
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ResumeGameFromUI();

	/** Resumes the game from a paused state (e.g., from the pause menu). */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResumeGame();

	/** Quits the current match and returns to the main menu. */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void QuitToMainMenu();
};
