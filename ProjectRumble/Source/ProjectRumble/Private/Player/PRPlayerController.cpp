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
		// ... (Move, Look, Jump baðlama kodlarýn burada) ...

		// --- BIND THE NEW ACTION ---
		EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &APRPlayerController::ToggleInventoryScreen);
	}
}

void APRPlayerController::ShowLevelUpScreen(int32 NewLevel)
{
	// Create an instance of our Reward Manager
	UPRRewardManager* RewardManager = NewObject<UPRRewardManager>();
	// --- SETUP THE REWARD MANAGER ---
	// Initialize the manager with the stat info data table.
	RewardManager->Initialize(StatsInfoDataTable);

	if (!RewardManager || AllPossibleItems.Num() == 0 || !LevelUpWidgetClass) return;

	// Get the player's inventory from the PlayerState
	UPRInventoryComponent* PlayerInventory = nullptr;
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		PlayerInventory = PS->InventoryComponent;
	}

	

	// Call the manager with the new parameters to get our rewards
	OfferedRewards = RewardManager->GenerateRewards(PlayerInventory, AllPossibleItems, 3);

	// --- Show UI (Bu kýsým ayný) ---
	SetPause(true);

	LevelUpWidgetInstance = CreateWidget(this, LevelUpWidgetClass);
	if (LevelUpWidgetInstance)
	{
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

	// --- Resume Game (This part stays the same) ---
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->RemoveFromParent();
	}

	SetPause(false);
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}
