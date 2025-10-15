// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PRHUD.h"
#include "Blueprint/UserWidget.h"

void APRHUD::BeginPlay()
{
    Super::BeginPlay();

    if (PlayerHUDWidgetClass)
    {
        PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
        if (PlayerHUDWidget)
        {
            PlayerHUDWidget->AddToViewport();
        }
    }
}
