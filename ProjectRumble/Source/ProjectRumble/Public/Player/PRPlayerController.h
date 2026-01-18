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
class UCommonActivatableWidget;

UCLASS()
class PROJECTRUMBLE_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APRPlayerController();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// -- CORE REPLICATION  --
	virtual void OnRep_Pawn() override;
	virtual void OnRep_PlayerState() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	// -- INPUT --
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> ToggleInventoryAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputAction> PauseAction;

	// -- DATA & REWARDS --

	//An array of Data Assets that holds all possible ITEMS (Weapons, Tomes, etc.) available in the level up pool.
	UPROPERTY(EditDefaultsOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRItemDefinition>> AllPossibleLevelUpItems;

	// Array to hold the rewards that are currently being offered to the player. We make it BlueprintReadOnly so the UI can read it.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_OfferedRewards, Category = "Rewards")
	TArray<TObjectPtr<UPRUpgradeData>> OfferedRewards;
	
	// This is our main STAT definition table.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> StatsInfoDataTable;

	// -- UI CLASSES --

	// Level Up Screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCommonActivatableWidget> LevelUpWidgetClass;

	// Inventory Screen
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidget> InventoryScreenWidgetClass;

	// Item Found Popup (Bunu da güncelledik)
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidget> ItemFoundPopupWidgetClass;

	// Pause Menu
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidget> PauseMenuWidgetClass;

	// Game Over
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UCommonActivatableWidget> GameOverWidgetClass;
	// -- INTERNAL LOGIC --

	// Tracks if THIS controller currently has the pause menu open.
	bool bIsPauseMenuOpen = false;
	// Called when the ToggleInventoryAction is triggered.
	void ToggleInventoryScreen();

	/** Called locally when the pause input is pressed. Sends a request to the server. */
	void TogglePauseMenu();

	// --- LEVEL UP SYSTEM ---

	// Called by the StatsComponent's OnLevelUpDelegate.
	UFUNCTION()
	void ShowLevelUpScreen(int32 NewLevel);

	// Called when OfferedRewards is replicated.
	UFUNCTION()
	void OnRep_OfferedRewards();

	FTimerHandle RetryHandle;

	// --- SERVER RPCs (STATE CHANGERS) ---
	/** Tells server we are opening the Pause Menu (locks game). */
	UFUNCTION(Server, Reliable)
	void Server_SetPauseMenuState(bool bIsOpen);

	/** Tells server we finished Level Up selection (unlocks game). */
	UFUNCTION(Server, Reliable)
	void Server_ApplyReward(UPRUpgradeData* ChosenUpgrade);

	/** Tells server we opened the Level Up widget (locks game). */
	UFUNCTION(Server, Reliable)
	void Server_PauseGameForLevelUp();

	// Function to capture the signal coming from Slate
	void OnWindowFocusChanged(bool bIsFocused);

public:
	// --- CLIENT RPCs (UI TRIGGERS) ---

	/** Tells client to show/hide pause menu widget. */
	UFUNCTION(Client, Reliable)
	void Client_TogglePauseMenuUI(bool bOpen);

	UFUNCTION(Client, Reliable)
	void Client_ShowRewardPopup(UPRUpgradeData* RewardToDisplay);

	UFUNCTION(Client, Unreliable)
	void Client_ShowDamageEffect(AActor* TargetActor, float DamageAmount, bool bIsCritical, USoundBase* HitSound);

	/** [CLIENT] Shows the Game Over screen with stats. */
	UFUNCTION(Client, Reliable)
	void Client_ShowGameOverScreen(bool bWon);

	// --- PUBLIC INTERFACE ---

	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void ApplyReward(UPRUpgradeData* ChosenUpgrade);

	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void RequestRewards(UDataTable* LootPool, int32 NumToOffer, bool bGrantDirectly = true);

	/** Resumes the game (closes pause menu). Called by UI Button. */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void QuitToMainMenu();

	// --- PLAYER DEATH --

	/** [SERVER] Called when the pawn controlled by this controller dies. */
	UFUNCTION(Server, Reliable)
	void Server_OnPlayerDied();

	// --- DEBUG ---

	UFUNCTION(Exec)
	void PrintStats();
};
