// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRTypes.h"
#include "PRItemDefinition.generated.h"

class UPRBaseItem;

UCLASS()
class PROJECTRUMBLE_API UPRItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
    // -- IDENTITY --
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    TObjectPtr<UTexture2D> Icon;

    // What type of item is this?
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    EItemType ItemType;
    // ... in the future, things like TSubclassOf<AActor> WeaponActorClass will be added for weapons ...

    // -- UPGRADE LOGIC --
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades|Effect Count")
    int32 NumEffects_Common = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades|Effect Count")
    int32 NumEffects_Uncommon = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades|Effect Count")
    int32 NumEffects_Rare = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades|Effect Count")
    int32 NumEffects_Epic = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades|Effect Count")
    int32 NumEffects_Legendary = 3;

    // A list of ALL possible stat upgrades this item can get when it levels up.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrades")
    TArray<FPotentialUpgradeEffect> PotentialUpgradeEffects;
    /**
    * The C++ class that holds the logic for this item.
    * e.g., UPRWeaponItem for weapons, UPRTomeItem for tomes.
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Logic")
    TSubclassOf<UPRBaseItem> ItemClass;
};
