// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRRewardManager.h"
#include "Components/PRInventoryComponent.h"

TArray<UPRUpgradeData*> UPRRewardManager::GenerateAndDraftRewards(const TArray<UDataTable*>& AllUpgradePools, const UPRInventoryComponent* PlayerInventory, int32 NumOfChoices)
{
	// --- 1. BUILD THE POOL OF ALL POSSIBLE REWARDS ---
	TArray<FUpgradePoolEntry> MasterPool = BuildMasterRewardPool(AllUpgradePools, PlayerInventory);

	// --- 2. DRAFT THE REWARDS ---
	TArray<UPRUpgradeData*> OfferedRewards;
	float TotalWeight = 0.f;

	// Calculate total weight for weighted random selection
	for (const FUpgradePoolEntry& Entry : MasterPool)
	{
		TotalWeight += Entry.Weight;
	}

	for (int32 i = 0; i < NumOfChoices; ++i)
	{
		if (MasterPool.Num() == 0 || TotalWeight <= 0.f)
		{
			break; // Stop if we run out of options
		}

		float RandomValue = FMath::FRandRange(0.f, TotalWeight);
		float CurrentWeight = 0.f;

		for (int32 j = 0; j < MasterPool.Num(); ++j)
		{
			CurrentWeight += MasterPool[j].Weight;
			if (RandomValue <= CurrentWeight)
			{
				// We've selected this reward
				OfferedRewards.Add(MasterPool[j].UpgradeDataAsset);

				// Remove it from the pool so it can't be picked again in the same draft
				TotalWeight -= MasterPool[j].Weight;
				MasterPool.RemoveAt(j);
				break;
			}
		}
	}

	return OfferedRewards;
}

TArray<FUpgradePoolEntry> UPRRewardManager::BuildMasterRewardPool(const TArray<UDataTable*>& AllUpgradePools, const UPRInventoryComponent* PlayerInventory)
{
	TArray<FUpgradePoolEntry> MasterPool;

	// For now, our logic is very simple: just add everything from all pools.
	// In the future, this function will be much smarter.
	// It will check player's inventory, item levels, etc.

	for (UDataTable* PoolTable : AllUpgradePools)
	{
		if (PoolTable)
		{
			FString ContextString; // Required for FindRow
			TArray<FName> RowNames = PoolTable->GetRowNames();

			for (const FName& RowName : RowNames)
			{
				FUpgradePoolEntry* Entry = PoolTable->FindRow<FUpgradePoolEntry>(RowName, ContextString);
				if (Entry && Entry->UpgradeDataAsset)
				{
					// TODO: Add logic here to filter out upgrades the player can't get
					// For example: if(Entry->UpgradeDataAsset->UpgradeType == EUpgradeType::UpgradeWeapon && !PlayerInventory->HasWeapon(Entry->UpgradeDataAsset->ItemClass)) { continue; }

					MasterPool.Add(*Entry);
				}
			}
		}
	}

	return MasterPool;
}
