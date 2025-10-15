// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PRTypes.h" 
#include "PRRewardManager.generated.h"

class UDataTable;
class UPRUpgradeData; // Forward Declaration
class UPRInventoryComponent; // Forward Declaration

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
	 * Main function to generate and draft a list of rewards for the player.
	 * @param AllUpgradePools An array of Data Tables to draw rewards from.
	 * @param PlayerInventory A reference to the player's inventory to check current items.
	 * @param NumOfChoices The number of rewards to offer the player.
	 * @return An array of offered upgrade data assets.
	 */
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	TArray<UPRUpgradeData*> GenerateAndDraftRewards(const TArray<UDataTable*>& AllUpgradePools, const UPRInventoryComponent* PlayerInventory, int32 NumOfChoices);


protected:
	/**
	 * Builds a master list of all possible upgrades based on the player's current state.
	 * @param AllUpgradePools All available upgrade data tables.
	 * @param PlayerInventory The player's current inventory.
	 * @return A weighted list of possible upgrades.
	 */
	TArray<FUpgradePoolEntry> BuildMasterRewardPool(const TArray<UDataTable*>& AllUpgradePools, const UPRInventoryComponent* PlayerInventory);
};
