// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PRHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API APRHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
    // The main gameplay widget class to create.
    // We assign this in the Blueprint derived from this class.
    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    // The instance of our main gameplay widget.
    UPROPERTY()
    TObjectPtr<UUserWidget> PlayerHUDWidget;

    // Called when the game starts.
    virtual void BeginPlay() override;

};
