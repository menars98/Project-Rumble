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
#include "UI/Widgets/PRPrimaryGameLayout.h" 
#include "CommonActivatableWidget.h"
#include "Interfaces/PRBPIPlayerHUD.h"
#include "Interfaces/PRBPIRewardScreen.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/PRCharacterBase.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "Engine/TimerHandle.h"
#include "FunctionLibrary/PRGameplayStatics.h"
#include "GameModes/PRGameMode.h"
#include "Components/PRSessionTrackerComponent.h"

APRPlayerController::APRPlayerController()
{
	bReplicates = true; 
}

void APRPlayerController::BeginPlay()
{
    Super::BeginPlay();
	 // Determine if we are on the server or client
    FString RoleString = HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT");
	UE_LOG(LogTemp, Warning, TEXT("[%s] PlayerController BeginPlay for %s."), *RoleString, *GetName());
}

void APRPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APRPlayerController, OfferedRewards);
}

bool APRPlayerController::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	// Replicate each offered reward upgrade data
	for (UPRUpgradeData* UpgradeData : OfferedRewards)
	{
		if (UpgradeData)
		{
			bWroteSomething |= Channel->ReplicateSubobject(UpgradeData, *Bunch, *RepFlags);
		}
	}

	return bWroteSomething;
}

void APRPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
// Server-side Setup
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (APRHUD* PRHUD = Cast<APRHUD>(GetHUD()))
		{
			PRHUD->InitializeHUDStats(PS);
		}
		if (UPRStatsComponent* StatsComp = PS->StatsComponent)
		{
			StatsComp->OnLevelUpDelegate.AddDynamic(this, &APRPlayerController::ShowLevelUpScreen);
		}
	}

	// If it's a Game Character, apply gameplay input settings
	if (Cast<APRCharacterBase>(InPawn))
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}

	UE_LOG(LogTemp, Warning, TEXT("[SERVER] OnPossess for %s"), *GetName());

}

void APRPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();

	// Client-side Input Setup
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	// We could also initialize client-side UI elements here if needed.
}

void APRPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// CLIENT SIDE SETUP
	// PlayerState is now valid. Let's initialize the HUD.
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (APRHUD* PRHUD = Cast<APRHUD>(GetHUD()))
		{
			// Send the component to the HUD widget
			PRHUD->InitializeHUDStats(PS);
		}
	}
}

void APRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// --- BIND THE NEW ACTION ---
		if (ToggleInventoryAction)
		{
			EnhancedInputComponent->BindAction(ToggleInventoryAction, ETriggerEvent::Started, this, &APRPlayerController::ToggleInventoryScreen);
		}
		// --- BIND PAUSE ACTION ---
		if (PauseAction)
		{
			EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APRPlayerController::TogglePauseMenu);
		}
	}
}

void APRPlayerController::TogglePauseMenu()
{
	// Local check to decide whether to Open or Close
	bool bShouldOpen = !bIsPauseMenuOpen;
	Server_SetPauseMenuState(bShouldOpen);
}

void APRPlayerController::ResumeGame()
{
	// Explicitly close the menu
	Server_SetPauseMenuState(false);
}

void APRPlayerController::Server_SetPauseMenuState_Implementation(bool bIsOpen)
{
	// Update Server State
	bIsPauseMenuOpen = bIsOpen;

	// Tell GameMode to lock/unlock the game globally
	if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (bIsOpen)
		{
			GM->RegisterPlayerInMenu();
		}
		else
		{
			GM->UnregisterPlayerInMenu();
		}
	}

	// Tell ALL clients (including owning client) to update UI
	// Why ALL? Because in Co-op, we might want to show "Player 2 Paused" text.
	// For now, we just tell THIS client to show the menu.
	Client_TogglePauseMenuUI(bIsOpen);
}

void APRPlayerController::Client_TogglePauseMenuUI_Implementation(bool bOpen)
{
	// Update Local State
	bIsPauseMenuOpen = bOpen;

	if (bOpen)
	{
		// Open Menu
		if (PauseMenuWidgetClass && !PauseMenuInstance)
		{
			PauseMenuInstance = CreateWidget(this, PauseMenuWidgetClass);
			PauseMenuInstance->AddToViewport();
		}
		FInputModeGameAndUI InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
	else
	{
		// Close Menu
		if (PauseMenuInstance)
		{
			PauseMenuInstance->RemoveFromParent();
			PauseMenuInstance = nullptr;
		}
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		bShowMouseCursor = false;
	}
}

void APRPlayerController::ShowLevelUpScreen(int32 NewLevel)
{
	// --- 1. VALIDATION ---
	if (!HasAuthority()) return;
	if (AllPossibleLevelUpItems.Num() == 0) return;

	// --- 2. PREPARE DATA ---
	UPRRewardManager* RewardManager = NewObject<UPRRewardManager>();
	if (!RewardManager) return;

	RewardManager->Initialize(StatsInfoDataTable);

	UPRInventoryComponent* PlayerInventory = GetPlayerState<APRPlayerState>() ? GetPlayerState<APRPlayerState>()->InventoryComponent : nullptr;

	// --- 3. GENERATE REWARDS ---
	OfferedRewards = RewardManager->GenerateRewards(PlayerInventory, AllPossibleLevelUpItems, 3);

	ForceNetUpdate();

	// --- 4. SEND TO CLIENT ---
	// We are not calling the Client RPC! We are waiting for OnRep to run.
	// However, OnRep does not run automatically for the Host (Listen Server); we must call it manually.
	if (IsLocalPlayerController())
	{
		OnRep_OfferedRewards();
	}

	// @TODO: We can send pause widget info to other player(s) here if needed.
}

void APRPlayerController::OnRep_OfferedRewards()
{
	// --- 1. VALIDATION ---
	if (!IsLocalPlayerController()) return;

	// Clear retry timer if active
	GetWorld()->GetTimerManager().ClearTimer(RetryHandle);

	if (OfferedRewards.Num() == 0) return;

	// Check for nulls
	for (UPRUpgradeData* Data : OfferedRewards)
	{
		if (Data == nullptr)
		{
			GetWorld()->GetTimerManager().SetTimer(RetryHandle, this, &APRPlayerController::OnRep_OfferedRewards, 0.1f, false);
			return;
		}
	}

	// --- Common UI Part ---

	APRHUD* CurrentHUD = Cast<APRHUD>(GetHUD());
	if (CurrentHUD && LevelUpWidgetClass)
	{
		UPRPrimaryGameLayout* RootLayout = CurrentHUD->GetMainLayout();
		if (RootLayout)
		{
			// 1. Push the widget to the Menu layer (It will automatically activate -> Play sound)
			FGameplayTag MenuLayerTag = NativeGameplayTags::UI_Layers::TAG_UI_Layer_Menu;

			// Note: We'll need to modify the PushWidget function slightly because 
			// we need the widget instance (to send the data).

			// We'll write a function that pushes through RootLayout and returns the Widget
			// OR let's do it manually for now:

			// Our current PushWidgetToLayer function returns void.
			// So first, let's find the stack and add it manually, or update the function.
			// The cleanest solution: Update PRPrimaryGameLayout. (Explained below)

			// For now, conceptually:
			UCommonActivatableWidget* CreatedWidget = RootLayout->PushWidgetToLayer(MenuLayerTag, LevelUpWidgetClass);

			// 2. Send data to the widget
			if (CreatedWidget && CreatedWidget->Implements<UPRBPIRewardScreen>())
			{
				IPRBPIRewardScreen::Execute_InitializeScreen(CreatedWidget, OfferedRewards);
			}

			// 3. Change Input Mode
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = true;

			Server_PauseGameForLevelUp();
		}
	}
}

void APRPlayerController::Server_PauseGameForLevelUp_Implementation()
{
	if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->RegisterPlayerInMenu();
	}
}

// Called by the PlayerCharacter when it dies.
void APRPlayerController::Server_OnPlayerDied_Implementation()
{
	if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		// Let the GameMode check if all players are dead.
		GM->CheckPlayerDeaths();
	}
}

void APRPlayerController::Client_ShowGameOverScreen_Implementation(bool bWon)
{
	if (GameOverWidgetClass)
	{
		// Clean UI
		if (LevelUpWidgetInstance) LevelUpWidgetInstance->RemoveFromParent();
		// Hide HUD if needed?
		if (APRHUD* PRHUD = Cast<APRHUD>(GetHUD()))
		{
			// PRHUD->HideHUD(); // @TODO: We need to add HideHUD function to the HUD interface.
		}

		UUserWidget* GameOverWidget = CreateWidget(this, GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();

			// Set Input Mode
			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = true;

			// We can send other info here if needed (like stats, score, etc.)
		}
	}

	// Pause game locally?
	// UGameplayStatics::SetGamePaused(GetWorld(), true); // But we don't want to pause the server.
}

void APRPlayerController::ApplyReward(UPRUpgradeData* ChosenUpgrade)
{
	if (!ChosenUpgrade) return;

	// --- COMMON UI KAPATMA MANTIÐI ---
	APRHUD* CurrentHUD = Cast<APRHUD>(GetHUD());
	if (CurrentHUD)
	{
		UPRPrimaryGameLayout* RootLayout = CurrentHUD->GetMainLayout();
		if (RootLayout)
		{
			// Menu katmanýndaki aktif widget'ý bul (Level Up ekraný oradadýr)
			FGameplayTag MenuLayerTag = NativeGameplayTags::UI_Layers::TAG_UI_Layer_Menu;
			UCommonActivatableWidget* ActiveMenu = RootLayout->GetActiveWidgetInLayer(MenuLayerTag);

			// Eðer bulduðun þey bizim LevelUp widget'ý ise kapat
			if (ActiveMenu && ActiveMenu->IsA(LevelUpWidgetClass))
			{
				ActiveMenu->DeactivateWidget();
			}
		}
	}

	// Input modunu geri al
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;

	// Server'a iþle
	Server_ApplyReward(ChosenUpgrade);
}

void APRPlayerController::Server_ApplyReward_Implementation(UPRUpgradeData* ChosenUpgrade)
{
	// Apply reward on the server side
	// The PlayerController's ONLY job is to forward the request to the correct component.
	// It doesn't need to know HOW the reward is applied.
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (UPRInventoryComponent* InvComp = PS->InventoryComponent)
		{
			InvComp->AddOrUpgradeItem(ChosenUpgrade);
		}
	}
	// --- UNPAUSE THE GAME ---
	if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GM->UnregisterPlayerInMenu();
	}
}

void APRPlayerController::RequestRewards(UDataTable* LootPool, int32 NumToOffer, bool bGrantDirectly)
{
	// --- 1. VALIDATION ---
	// Make sure we have a valid LootPool to draw from and a valid number of offers.
	if (!LootPool || NumToOffer <= 0 || !HasAuthority())
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
		if (bGrantDirectly)
		{
			// 1. PAUSE THE GAME (Global Pause)
			if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
			{
				GM->RegisterPlayerInMenu();
			}

			// 2. SEND TO CLIENT
			Client_ShowRewardPopup(GeneratedRewards[0]);

			//// Create the popup widget
			//UUserWidget* PopupWidget = CreateWidget(this, ItemFoundPopupWidgetClass);

			//// Now, we need to pass the data to it. We need an interface or a cast.
			//// Let's use an interface for this, it's cleaner.
			//// Assuming WBP_ItemFoundPopup implements BPI_ItemPopup
			//if (PopupWidget->GetClass()->ImplementsInterface(UPRBPIRewardScreen::StaticClass()))
			//{
			//	// Call the interface function to initialize the widget with the reward data.
			//	IPRBPIRewardScreen::Execute_InitializeScreen(PopupWidget, GeneratedRewards);
			//	PopupWidget->AddToViewport();
			//}

			//@TODO: // Client_ShowRewardPopup(GeneratedRewards[0]); 
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

void APRPlayerController::Client_ShowRewardPopup_Implementation(UPRUpgradeData* RewardToDisplay)
{
	// --- VALIDATION ---
	if (ItemFoundPopupWidgetClass)
	{
		// --- CREATE WIDGET ---
		UUserWidget* PopupWidget = CreateWidget(this, ItemFoundPopupWidgetClass);

		if (PopupWidget)
		{
			// --- STORE REFERENCE ---
			LevelUpWidgetInstance = PopupWidget;

			// --- INITIALIZE WITH DATA ---
			if (PopupWidget->GetClass()->ImplementsInterface(UPRBPIRewardScreen::StaticClass()))
			{
				TArray<UPRUpgradeData*> SingleRewardArray;
				SingleRewardArray.Add(RewardToDisplay);
				IPRBPIRewardScreen::Execute_InitializeScreen(PopupWidget, SingleRewardArray);
			}

			PopupWidget->AddToViewport();

			FInputModeUIOnly InputMode;
			SetInputMode(InputMode);
			bShowMouseCursor = true;
		}
	}
}

void APRPlayerController::Client_ShowDamageEffect_Implementation(AActor* TargetActor, float DamageAmount, bool bIsCritical, USoundBase* HitSound)
{
	if (!TargetActor) return;

	// 1. Show Damage Number (Only visible to player)
	// We use 'this' as WorldContext because we are inside the local controller now.
	UPRGameplayStatics::SpawnDamageNumber(this, DamageAmount, bIsCritical, TargetActor);

	// 2. Play Hit Sound (Only audible to player)
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, TargetActor->GetActorLocation());
	}
}

void APRPlayerController::ToggleInventoryScreen()
{
	APRHUD* CurrentHUD = Cast<APRHUD>(GetHUD());
    if (!CurrentHUD || !InventoryScreenWidgetClass) return;

    UPRPrimaryGameLayout* RootLayout = CurrentHUD->GetMainLayout();
    if (!RootLayout) return;

    FGameplayTag MenuLayerTag = NativeGameplayTags::UI_Layers::TAG_UI_Layer_Menu;

	// 1. Find the currently active widget on that layer
    UCommonActivatableWidget* ActiveWidget = RootLayout->GetActiveWidgetInLayer(MenuLayerTag);

	// 2. CHECK: Is the active widget our Inventory?
    if (ActiveWidget && ActiveWidget->IsA(InventoryScreenWidgetClass))
    {
        // (Deactivate)
        ActiveWidget->DeactivateWidget();
    }
    else
    {
		// Closed or another menu is present -> OPEN (Push)
        RootLayout->PushWidgetToLayer(MenuLayerTag, InventoryScreenWidgetClass);
    }
}

void APRPlayerController::QuitToMainMenu()
{
	// Unpause the game before changing levels, just in case.
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// TODO: Replace "MainMenu_L" with the actual name of your main menu map.
	UGameplayStatics::OpenLevel(this, FName("MainMenu_L"), true);
}

void APRPlayerController::PrintStats()
{
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		if (PS->TrackerComponent)
		{
			// If we are client, we might not have the "InternalMap", 
			// but we can iterate the "ReplicatedStats" array if we want client-side logs.
			// However, Server log is usually more accurate during dev.

			// Since DebugLogAllStats uses InternalMap, it works best on Server.
			PS->TrackerComponent->DebugLogAllStats();
		}
	}
}