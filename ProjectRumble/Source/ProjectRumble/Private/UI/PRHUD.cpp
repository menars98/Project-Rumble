// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRHUD.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/PRBPIPlayerHUD.h"
#include <Player/PRPlayerState.h>
#include "UI/Widgets/PRPrimaryGameLayout.h"
#include "PRGameplayTags.h" 
#include "CommonActivatableWidget.h"


void APRHUD::InitializeHUDStats(APRPlayerState* PlayerState)
{
    if (!MainLayout || !PlayerState) return;

    // 1. Take GameLayer Tag
    FGameplayTag GameLayerTag = NativeGameplayTags::UI_Layers::TAG_UI_Layer_Game;

    // 2. Get the active widget in that layer
    UCommonActivatableWidget* ActiveHUDWidget = MainLayout->GetActiveWidgetInLayer(GameLayerTag);

	// 3. Does the widget implement our HUD interface?
    if (ActiveHUDWidget && ActiveHUDWidget->Implements<UPRBPIPlayerHUD>())
    {
        // 4. Send the data (Triggers the “Event Setup HUD” in Blueprint)
        IPRBPIPlayerHUD::Execute_SetupHUD(ActiveHUDWidget, PlayerState);

        UE_LOG(LogTemp, Log, TEXT("PRHUD: Initialized HUD Stats via CommonUI Layer."));
    }
    else
    {
        // The widget may not have been created yet (Race Condition), this is normal.
        // WBP_PlayerHUD will update itself at the “Construct” stage, so this is not critical.
        // However, this is useful in Host/Server scenarios.
        UE_LOG(LogTemp, Warning, TEXT("PRHUD: Could not find active HUD widget in Game Layer to initialize."));
    }
}

void APRHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MainLayoutClass)
    {
        // 1. Create Layout
        MainLayout = CreateWidget<UPRPrimaryGameLayout>(GetOwningPlayerController(), MainLayoutClass);
        if (MainLayout)
        {
            MainLayout->AddToViewport();

            if (APRPlayerState* PS = GetOwningPlayerController()->GetPlayerState<APRPlayerState>())
            {
                InitializeHUDStats(PS);
            }
        }
    }
}
