// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PRHUD.generated.h"

class UPRStatsComponent;
class APRPlayerState;
class UPRPrimaryGameLayout;

UCLASS()
class PROJECTRUMBLE_API APRHUD : public AHUD
{
	GENERATED_BODY()

public:
    /** Returns the Main Layout container */
    UFUNCTION(BlueprintPure, Category = "UI")
    class UPRPrimaryGameLayout* GetMainLayout() const { return MainLayout; }
	
    void InitializeHUDStats(APRPlayerState* PlayerState);

protected:
    //// The main gameplay widget class to create.
    //// We assign this in the Blueprint derived from this class.
    //UPROPERTY(EditDefaultsOnly, Category = "Widgets")
    //TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    // The instance of our main gameplay widget.
    /*UPROPERTY()
    TObjectPtr<UUserWidget> PlayerHUDWidget;*/

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UPRPrimaryGameLayout> MainLayoutClass;

    UPROPERTY()
    TObjectPtr<UPRPrimaryGameLayout> MainLayout;

    // Called when the game starts.
    virtual void BeginPlay() override;

};
