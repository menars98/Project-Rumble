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

class UPRItemDefinition;

UCLASS(BlueprintType)
class PROJECTRUMBLE_API UPRUpgradeData : public UObject
{
	GENERATED_BODY()
	
public:
	// -- DISPLAY & IDENTITY --
	// These properties will be FILLED IN AT RUNTIME by the RewardManager.

	/** The final, resolved name to show on the card (e.g., "Elven Bow"). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Display")
	FText DisplayName;

	/** The final, resolved description to show (e.g., "Damage: +12.7%\nProjectile Speed: +0.35"). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Display", meta = (MultiLine = true))
	FText Description;

	/** The icon to display. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Display")
	TObjectPtr<UTexture2D> Icon;

	/** The final, resolved rarity of this specific upgrade offer. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Display")
	EUpgradeRarity Rarity;

	/** The level this upgrade represents (e.g., "LVL 2"). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Display")
	int32 UpgradeLevel;

	// -- LOGIC --
	// This array holds the FINAL, "rolled" effects that will be applied if this upgrade is chosen.
	// All magnitudes are now fixed numbers, not ranges.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
	TArray<FUpgradeEffect> Effects;
	// A reference back to the "rulebook" this offer was generated from.
	// The InventoryComponent will use this to know which item to add or upgrade.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Logic")
	TObjectPtr<UPRItemDefinition> SourceItemDefinition;


	// We no longer need:
	// - EUpgradeType
	// - ItemClass
	// - TargetStat
	// - StatValue
	// - Rarity-based effect counts
	// All of that logic now lives in the ItemDefinition and is processed by the RewardManager.
	// This class is just a simple data container.
};
