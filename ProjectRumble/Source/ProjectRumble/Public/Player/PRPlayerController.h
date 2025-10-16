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

UCLASS()
class PROJECTRUMBLE_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;


protected:
	// -- REWARD SYSTEM --
	// An array of Data Assets that holds all possible items (weapons, tomes) in the game.
	// We will assign this in the BP_PlayerController Blueprint.
	// This replaces the old RewardDataTable.
	UPROPERTY(EditDefaultsOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRItemDefinition>> AllPossibleItems;

	// Array to hold the rewards that are currently being offered to the player.
	// We make it BlueprintReadOnly so the UI can read it.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRUpgradeData>> OfferedRewards;

	// This is our main STAT definition table.
	UPROPERTY(EditDefaultsOnly, Category = "Data")
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

	// -- CORE --
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

	// Called when the ToggleInventoryAction is triggered.
	void ToggleInventoryScreen();

	
public:
	// Called by the UI Widget when a player clicks on a reward button.
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void ApplyReward(UPRUpgradeData* ChosenUpgrade);
};
