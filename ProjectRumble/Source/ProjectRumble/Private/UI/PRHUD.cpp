// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRHUD.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/PRBPIPlayerHUD.h"
#include <Player/PRPlayerState.h>

void APRHUD::InitializeHUDStats(UPRStatsComponent* StatsComp)
{
	if (PlayerHUDWidget)
	{

		IPRBPIPlayerHUD::Execute_SetupHUD(PlayerHUDWidget, StatsComp); 

	}
}

void APRHUD::BeginPlay()
{
    Super::BeginPlay();

    if (PlayerHUDWidgetClass)
    {
        // 1. Create Widget
        PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
        if (PlayerHUDWidget)
        {
            PlayerHUDWidget->AddToViewport();

            // --- 2. EARLY STARTUP FOR SERVER/HOST ---
            // The widget definitely exists now. Let's check if PlayerState is ready.
            if (APlayerController* PC = GetOwningPlayerController())
            {
                if (APRPlayerState* PS = PC->GetPlayerState<APRPlayerState>())
                {
                    if (PS->StatsComponent)
                    {
                        InitializeHUDStats(PS->StatsComponent);
                        UE_LOG(LogTemp, Warning, TEXT("[HUD] Initialized directly in BeginPlay (Server/Host path)."));
                    }
                }
            }
        }
    }
}
