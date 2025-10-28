// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PRGameInstance.generated.h"

class UDataTable;

UCLASS()
class PROJECTRUMBLE_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	/** The widget class to use for displaying floating damage numbers. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<class UPRWorldUserWidget> DamageNumberWidgetClass;

    /** The Data Table containing definitions for all loot profiles in the game. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<class UDataTable> LootProfileTable;
};
