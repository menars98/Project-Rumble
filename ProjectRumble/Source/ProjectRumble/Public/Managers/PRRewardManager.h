// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PRTypes.h" 
#include "Datas/PRUpgradeData.h"
#include "Datas/PRItemDefinition.h"
#include "PRRewardManager.generated.h"



class UPRItemDefinition; 
class UPRInventoryComponent;

/**
 *  Manages the logic for generating and drafting level-up rewards.
 *  This is a transient UObject, created when needed.
 */
UCLASS()
class PROJECTRUMBLE_API UPRRewardManager : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * Sets up the Reward Manager with the necessary data sources before use.
	 * @param InStatsInfoTable A Data Table containing display names for stats.
	 */
	void Initialize(UDataTable* InStatsInfoTable);


	/**
	 * Main function to generate a list of rewards for the player.
	 * @param PlayerInventory A reference to the player's inventory to check current items.
	 * @param AllPossibleItems A list of all item definitions the player could potentially get.
	 * @param NumOfChoices The number of rewards to offer the player.
	 * @param PlayerLevel The player's current level, for scaling purposes.
	 * @return An array of dynamically generated upgrade data objects.
	 */
	TArray<UPRUpgradeData*> GenerateRewards(const UPRInventoryComponent* PlayerInventory, const TArray<UPRItemDefinition*>& AllPossibleItems, int32 NumOfChoices);


protected:
	/**
	 * Generates a single, fully-formed upgrade offer for a specific item.
	 * This function handles rarity rolls, effect selection, and value rolls.
	 * @param ItemDef The definition of the item to generate an upgrade for.
	 * @param PlayerInventory A reference to the player's inventory to check current items.
	 * @param bIsNewItem If true, this will be a "pick up new item" offer. Otherwise, it's a level-up offer.
	 * @return A dynamically created UPRUpgradeData object.
	 */
	UPRUpgradeData* CreateUpgradeOfferForItem(UPRItemDefinition* ItemDef, const UPRInventoryComponent* PlayerInventory, bool bIsNewItem);

	/** Determines the rarity for an upcoming upgrade offer. */
	EUpgradeRarity RollForRarity();

private:
	// A pointer to the data table that holds stat definitions (display names, etc.).
	// This is set during Initialize.
	UPROPERTY()
	TObjectPtr<UDataTable> StatsInfoTable;
};
