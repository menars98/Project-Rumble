// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerController.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h" 
#include "Components/PRInventoryComponent.h"
#include "Managers/PRRewardManager.h"
#include "Datas/PRUpgradeData.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/PRHUD.h"
#include "Interfaces/PRBPIPlayerHUD.h"
#include "Interfaces/PRBPIRewardScreen.h"

void APRPlayerController::BeginPlay()
{
    Super::BeginPlay();

}

void APRPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Get our custom PlayerState
    if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
    {
        // Check if it has a valid StatsComponent
        if (UPRStatsComponent* StatsComp = PS->StatsComponent)
        {
            // Bind our function to the delegate
            StatsComp->OnLevelUpDelegate.AddDynamic(this, &APRPlayerController::ShowLevelUpScreen);
        }
    }
}

void APRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{

		// --- BIND THE NEW ACTION ---
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &APRPlayerController::ToggleInventoryScreen);
	}
}

void APRPlayerController::ShowLevelUpScreen(int32 NewLevel)
{
	// --- 1. VALIDATION ---
	// Check if we have items to offer and a widget to show them with.
	if (AllPossibleLevelUpItems.Num() == 0 || !LevelUpWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ShowLevelUpScreen: No Level Up items or widget class assigned in PlayerController."));
		return;
	}

	// --- 2. PREPARE THE MANAGER AND DATA ---
	UPRRewardManager* RewardManager = NewObject<UPRRewardManager>();
	if (!RewardManager) return;

	RewardManager->Initialize(StatsInfoDataTable);

	UPRInventoryComponent* PlayerInventory = GetPlayerState<APRPlayerState>() ? GetPlayerState<APRPlayerState>()->InventoryComponent : nullptr;

	// --- 3. GENERATE REWARDS ---
	// Call the manager to get our LEVEL UP rewards from our specific level-up pool.
	OfferedRewards = RewardManager->GenerateRewards(PlayerInventory, AllPossibleLevelUpItems, 3);

	// --- 4. SHOW THE LEVEL UP UI ---
	SetPause(true);

	LevelUpWidgetInstance = CreateWidget(this, LevelUpWidgetClass);
	if (LevelUpWidgetInstance)
	{
		// Check if the widget implements our reward screen interface
		if (LevelUpWidgetInstance->GetClass()->ImplementsInterface(UPRBPIRewardScreen::StaticClass()))
		{
			// Pass the generated rewards to the UI to display
			IPRBPIRewardScreen::Execute_InitializeScreen(LevelUpWidgetInstance, OfferedRewards);
		}

		LevelUpWidgetInstance->AddToViewport();
	}

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void APRPlayerController::ToggleInventoryScreen()
{
	// Get our custom HUD from the controller.
	APRHUD* CurrentHUD = Cast<APRHUD>(GetHUD());
	if (!CurrentHUD)
	{
		// If we don't have our custom HUD for some reason, we can't do anything.
		return;
	}

	// Get the main player HUD widget instance from our HUD class.
	UUserWidget* PlayerHUDWidget = CurrentHUD->GetPlayerHUDWidget();
	if (!PlayerHUDWidget)
	{
		// If the main HUD widget hasn't been created yet, we can't do anything.
		return;
	}

	// --- THIS IS THE INTERFACE LOGIC ---
	// Check if the main HUD widget implements our interface.
	if (PlayerHUDWidget->GetClass()->ImplementsInterface(UPRBPIPlayerHUD::StaticClass()))
	{
		// If it does, we can safely call the interface function on it.
		// We use Execute_FunctionName for BlueprintImplementableEvents.
		IPRBPIPlayerHUD::Execute_ToggleInventory(PlayerHUDWidget);
	}


	// --- INPUT MODE & MOUSE CURSOR LOGIC ---
	// This logic is independent of the widget and handles player input.
	// Let's assume the UI will tell us if it's now open or closed.
	// For a simpler approach, we can check the widget's visibility, but that creates a dependency.
	// A better way is to just toggle the state.

	const bool bIsInventoryOpen = bShowMouseCursor; // A simple way to check the current state

	if (bIsInventoryOpen)
	{
		// If it was open, we are closing it. Return to Game Only mode.
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}
	else
	{
		// If it was closed, we are opening it. Switch to Game and UI mode.
		FInputModeGameAndUI InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
}

void APRPlayerController::ApplyReward(UPRUpgradeData* ChosenUpgrade)
{
	if (!ChosenUpgrade) return;

	// The PlayerController's ONLY job is to forward the request to the correct component.
	// It doesn't need to know HOW the reward is applied.

	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (UPRInventoryComponent* InvComp = PS->InventoryComponent)
		{
			// Tell the InventoryComponent to handle this upgrade.
			InvComp->AddOrUpgradeItem(ChosenUpgrade);
		}
	}

	// --- Resume Game  ---
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->RemoveFromParent();
	}

	SetPause(false);
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}

void APRPlayerController::RequestRewards(UDataTable* LootPool, int32 NumToOffer, bool bGrantDirectly)
{
	// --- 1. VALIDATION ---
	// Make sure we have a valid LootPool to draw from and a valid number of offers.
	if (!LootPool || NumToOffer <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("RequestRewards called with invalid parameters."));
		return;
	}

	// --- 2. PREPARE THE MANAGER AND DATA ---
	// Create a transient Reward Manager to handle the logic.
	UPRRewardManager* RewardManager = NewObject<UPRRewardManager>();
	if (!RewardManager)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create RewardManager."));
		return;
	}

	// The manager needs the Stats Info Table to generate proper descriptions for rewards.
	RewardManager->Initialize(StatsInfoDataTable);

	// The manager needs the inventory to check if an item is new or an upgrade.
	UPRInventoryComponent* PlayerInventory = GetPlayerState<APRPlayerState>() ? GetPlayerState<APRPlayerState>()->InventoryComponent : nullptr;

	if (!PlayerInventory)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot grant rewards, PlayerInventory is not valid."));
		return;
	}

	// --- 3. GENERATE REWARDS USING THE CORRECT FUNCTION ---
	// Call the new function that is specifically designed to work with Loot Data Tables.
	TArray<UPRUpgradeData*> GeneratedRewards = RewardManager->GenerateLootRewards(PlayerInventory, LootPool, NumToOffer);

	// --- 4. GRANT THE REWARDS ---
	if (GeneratedRewards.Num() > 0)
	{
		if (bGrantDirectly && ItemFoundPopupWidgetClass)
		{
			// We don't grant it directly to the inventory anymore.
			// We show a popup UI instead.
			UPRUpgradeData* RewardToShow = GeneratedRewards[0];

			// Pause the game or at least ignore player input
		   // SetPause(true); // Pausing might be too disruptive. Let's just change input mode.
			SetPause(true);
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = true;

			// Create the popup widget
			UUserWidget* PopupWidget = CreateWidget(this, ItemFoundPopupWidgetClass);

			// Now, we need to pass the data to it. We need an interface or a cast.
			// Let's use an interface for this, it's cleaner.
			// Assuming WBP_ItemFoundPopup implements BPI_ItemPopup
			if (PopupWidget->GetClass()->ImplementsInterface(UPRBPIRewardScreen::StaticClass()))
			{
				// Call the interface function to initialize the widget with the reward data.
				IPRBPIRewardScreen::Execute_InitializeScreen(PopupWidget, GeneratedRewards);
				PopupWidget->AddToViewport();
			}
		}
		else
		{
			// This branch is for showing the level up screen with multiple choices
			// ...
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Loot pool '%s' generated no rewards."), *LootPool->GetName());
	}
}

void APRPlayerController::ResumeGameFromUI()
{
	SetPause(false); // If the game was paused
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}
