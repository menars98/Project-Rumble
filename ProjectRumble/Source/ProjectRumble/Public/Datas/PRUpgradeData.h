// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRTypes.h"
#include "PRGameplayTags.h"
#include "PRUpgradeData.generated.h"

UENUM(BlueprintType)
enum class EUpgradeRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Epic,
	Legendary
};

UCLASS(BlueprintType)
class PROJECTRUMBLE_API UPRUpgradeData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// The type of this upgrade. This determines how it will be applied.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	EUpgradeType UpgradeType;

	// The text displayed on the reward card.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	FText DisplayName;

	// A more detailed description of what this upgrade does.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	TObjectPtr<UTexture2D> Icon;

	// --- DATA FOR SPECIFIC UPGRADE TYPES ---
	// Which Weapon or Passive Item class does this upgrade relate to?
	// Used for 'NewWeapon', 'UpgradeWeapon', 'NewPassiveItem', 'UpgradePassiveItem'.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade Data", meta = (EditCondition = "UpgradeType != EUpgradeType::StatBonus"))
	TSubclassOf<UObject> ItemClass;

	// The rarity of this upgrade. This can affect its values and appearance.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	EUpgradeRarity Rarity;

	// This array holds all the effects this upgrade will apply.
	// A single upgrade can now modify multiple stats at once.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Upgrade")
	TArray<FUpgradeEffect> Effects;
};
