// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerController.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h" 
#include "Components/PRInventoryComponent.h"
#include "Managers/PRRewardManager.h"
#include "Datas/PRUpgradeData.h"
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

void APRPlayerController::ShowLevelUpScreen(int32 NewLevel)
{
	// Create an instance of our Reward Manager
	UPRRewardManager* RewardManager = NewObject<UPRRewardManager>();
	if (!RewardManager || !RewardDataTable || !LevelUpWidgetClass) return;

	// Prepare the pools for the manager
	TArray<UDataTable*> UpgradePools;
	UpgradePools.Add(RewardDataTable);

	// Get the player's inventory (currently null, which is fine for our prototype)
	UPRInventoryComponent* PlayerInventory = nullptr;

	// Call the manager to get our rewards and store them in the OfferedRewards array
	OfferedRewards = RewardManager->GenerateAndDraftRewards(UpgradePools, PlayerInventory, 3);

	// --- Show UI ---
	SetPause(true); // Pause the game

	// Create the widget
	LevelUpWidgetInstance = CreateWidget(this, LevelUpWidgetClass);
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->AddToViewport();
	}

	// Set input mode to UI only and show the mouse cursor
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void APRPlayerController::ApplyReward(UPRUpgradeData* ChosenUpgrade)
{
	if (!ChosenUpgrade) return;

	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (UPRStatsComponent* StatsComp = PS->StatsComponent)
		{
			// Loop through all effects in the chosen upgrade data asset
			for (const FUpgradeEffect& Effect : ChosenUpgrade->Effects)
			{
				// In the future, we will "roll" the value here. For now, let's use the Min value.
				float ValueToApply = Effect.MinMagnitude;

				float CurrentValue = StatsComp->GetStatValue(Effect.TargetStat);
				float NewValue = 0.f;

				// Apply the effect based on its operation type
				if (Effect.Operation == EModifierOperation::Additive)
				{
					NewValue = CurrentValue + ValueToApply;
				}
				else if (Effect.Operation == EModifierOperation::Multiplicative)
				{
					NewValue = CurrentValue + ValueToApply; // Note: For now, we also add multiplicative bonuses. A real system would be more complex.
				}

				StatsComp->SetStatValue(Effect.TargetStat, NewValue);
				UE_LOG(LogTemp, Warning, TEXT("Applied Reward '%s'! Stat '%s' changed to %f."), *ChosenUpgrade->DisplayName.ToString(), *Effect.TargetStat.ToString(), NewValue);
			}
		}
	}

	// --- Resume Game ---
	if (LevelUpWidgetInstance)
	{
		LevelUpWidgetInstance->RemoveFromParent();
	}

	SetPause(false);
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}
