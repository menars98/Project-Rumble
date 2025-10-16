// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerController.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h" 
#include "Components/PRInventoryComponent.h"
#include "Managers/PRRewardManager.h"
#include "Datas/PRUpgradeData.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"

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
	// Check if the widget is already created and visible
	if (InventoryScreenInstance && InventoryScreenInstance->IsInViewport())
	{
		// If it is, remove it.
		InventoryScreenInstance->RemoveFromParent();
		InventoryScreenInstance = nullptr; // Clear the pointer

		// Set input mode back to game only and hide the mouse cursor
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}
	else
	{
		// If it's not visible, create and show it.
		if (InventoryScreenWidgetClass)
		{
			InventoryScreenInstance = CreateWidget(this, InventoryScreenWidgetClass);
			if (InventoryScreenInstance)
			{
				InventoryScreenInstance->AddToViewport();

				// Set input mode to Game and UI and show the mouse cursor
				FInputModeGameAndUI InputMode;
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
		}
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
