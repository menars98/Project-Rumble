// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRTypes.h"
#include "PRUpgradeData.h"
#include "PRItemDefinition.generated.h"



class UPRBaseItem;

UCLASS(BlueprintType)
class PROJECTRUMBLE_API UPRItemDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
    // -- IDENTITY --
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Identity")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Identity")
    TObjectPtr<UTexture2D> Icon;

    // What type of item is this?
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Identity")
    EItemType ItemType;
   
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rarity", meta = (EditCondition = "bHasStaticRarity"))
    EUpgradeRarity StaticRarity = EUpgradeRarity::Common;

    // -- UPGRADE LOGIC --
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades|Effect Count")
    int32 NumEffects_Common = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades|Effect Count")
    int32 NumEffects_Uncommon = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades|Effect Count")
    int32 NumEffects_Rare = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades|Effect Count")
    int32 NumEffects_Epic = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades|Effect Count")
    int32 NumEffects_Legendary = 3;

    // A list of ALL possible stat upgrades this item can get when it levels up.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Upgrades")
    TArray<FPotentialUpgradeEffect> PotentialUpgradeEffects;
    /**
    * The C++ class that holds the logic for this item.
    * e.g., UPRWeaponItem for weapons, UPRPassiveItem for tomes.
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Item Logic")
    TSubclassOf<UPRBaseItem> ItemClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Identity")
    FGameplayTag ItemIdentityTag;

	// -- FUNCTIONS --
	// Override to indicate that this Data Asset supports networking.
    virtual bool IsSupportedForNetworking() const override { return true; }

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
