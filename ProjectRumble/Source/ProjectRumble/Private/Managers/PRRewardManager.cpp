// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRRewardManager.h"
#include "Datas/PRBaseItem.h"
#include "Components/PRInventoryComponent.h"

void UPRRewardManager::Initialize(UDataTable* InStatsInfoTable)
{
	StatsInfoTable = InStatsInfoTable;
}

TArray<UPRUpgradeData*> UPRRewardManager::GenerateRewards(const UPRInventoryComponent* PlayerInventory, const TArray<UPRItemDefinition*>& AllPossibleItems, int32 NumOfChoices)
{
	// TODO: Use PlayerInventory to decide which upgrades to offer
	// (e.g., offer "Upgrade Bow" only if player HAS a bow).

	TArray<UPRUpgradeData*> OfferedRewards;

	// --- BUILD A POOL OF POSSIBLE UPGRADE ACTIONS ---
	// This logic is simplified for now. A real system would be more complex.
	// For now, let's just pick random items from the "all items" list and generate an upgrade for them.
	// TODO: Prioritize items the player already has (for level-ups).
	// TODO: Add new, unowned items to the pool.

	TArray<UPRItemDefinition*> TempItemPool = AllPossibleItems;

	for (int32 i = 0; i < NumOfChoices; ++i)
	{
		if (TempItemPool.Num() == 0) break;

		int32 RandomIndex = FMath::RandRange(0, TempItemPool.Num() - 1);
		UPRItemDefinition* ChosenItemDef = TempItemPool[RandomIndex];
		
		// Check the inventory to see if this is a new item or an upgrade.
		bool bIsNewItemOffer = true;
		if (PlayerInventory)
		{
			if (PlayerInventory->FindItemByDefinition(ChosenItemDef))
			{
				// We already own this item, so it's an upgrade offer.
				bIsNewItemOffer = false;
			}
		}

		// Now, create the offer with the correct context (new or upgrade).
		UPRUpgradeData* NewOffer = CreateUpgradeOfferForItem(ChosenItemDef, PlayerInventory, bIsNewItemOffer);
		if (NewOffer)
		{
			OfferedRewards.Add(NewOffer);
		}

		TempItemPool.RemoveAt(RandomIndex);
	}

	return OfferedRewards;
}

UPRUpgradeData* UPRRewardManager::CreateUpgradeOfferForItem(UPRItemDefinition* ItemDef, const UPRInventoryComponent* PlayerInventory, bool bIsNewItem)
{
	if (!ItemDef) return nullptr;

	// --- 1. ROLL FOR RARITY ---
	EUpgradeRarity RolledRarity = RollForRarity();

	// --- 2. DETERMINE NUMBER OF EFFECTS ---
	int32 NumEffectsToPick = 0;
	switch (RolledRarity)
	{
	case EUpgradeRarity::Common:    NumEffectsToPick = ItemDef->NumEffects_Common; break;
	case EUpgradeRarity::Uncommon:  NumEffectsToPick = ItemDef->NumEffects_Uncommon; break;
	case EUpgradeRarity::Rare:      NumEffectsToPick = ItemDef->NumEffects_Rare; break;
	case EUpgradeRarity::Epic:      NumEffectsToPick = ItemDef->NumEffects_Epic; break;
	case EUpgradeRarity::Legendary: NumEffectsToPick = ItemDef->NumEffects_Legendary; break;
	}

	// --- 3. PICK RANDOM EFFECTS FROM THE ITEM'S POTENTIAL LIST ---
	TArray<FPotentialUpgradeEffect> PotentialEffects = ItemDef->PotentialUpgradeEffects;
	TArray<FPotentialUpgradeEffect> FinalEffects;
	FString FinalDescription = "";

	for (int32 i = 0; i < NumEffectsToPick; ++i)
	{
		if (PotentialEffects.Num() == 0) break;

		// TODO: Implement weighted random selection based on SelectionWeight.
		// For now, simple random is fine for a prototype.
		int32 RandomIndex = FMath::RandRange(0, PotentialEffects.Num() - 1);
		const FPotentialUpgradeEffect& ChosenPotentialEffect = PotentialEffects[RandomIndex];

		// --- Find the DisplayName for the stat ---
		FString StatDisplayName = "Unknown Stat";
		EStatDisplayType DisplayType = EStatDisplayType::Flat; // Default
		if (StatsInfoTable)
		{
			for (const FName& RowName : StatsInfoTable->GetRowNames())
			{
				FStatDefinition* StatDef = StatsInfoTable->FindRow<FStatDefinition>(RowName, "");
				if (StatDef && StatDef->StatID == ChosenPotentialEffect.TargetStat)
				{
					StatDisplayName = StatDef->DisplayName.ToString();
					DisplayType = StatDef->DisplayType; 
					break;
				}
			}
		}

		// --- 4. ROLL FOR THE MAGNITUDE ---
		float RarityBonus = (uint8)RolledRarity * ChosenPotentialEffect.BonusPerRarityTier;
		float RolledMagnitude = FMath::FRandRange(
			ChosenPotentialEffect.BaseMinMagnitude + RarityBonus,
			ChosenPotentialEffect.BaseMaxMagnitude + RarityBonus
		);

		// Create the final, resolved effect
		FPotentialUpgradeEffect FinalEffect;
		FinalEffect.TargetStat = ChosenPotentialEffect.TargetStat;
		// Store the FINAL rolled value in BOTH Min and Max to make it a fixed value.
		FinalEffect.BaseMinMagnitude = RolledMagnitude;
		FinalEffect.BaseMaxMagnitude = RolledMagnitude;

		FinalEffects.Add(FinalEffect);

		// --- Build the description string using the correct DisplayType ---
		switch (DisplayType)
		{
		case EStatDisplayType::Percentage:
			FinalDescription += FString::Printf(TEXT("%s: +%.1f%%\n"), *StatDisplayName, RolledMagnitude * 100);
			break;

		case EStatDisplayType::Multiplier:
			// For multipliers, we show the bonus amount, not the final value
			FinalDescription += FString::Printf(TEXT("%s: +%.1f%%\n"), *StatDisplayName, RolledMagnitude * 100);
			// Note: Or show as "+0.15x"? That's a design choice. Let's stick to percentage for clarity.
			break;

		case EStatDisplayType::Flat:
		default:
			FinalDescription += FString::Printf(TEXT("%s: +%.0f\n"), *StatDisplayName, RolledMagnitude);
			break;
		}

		PotentialEffects.RemoveAt(RandomIndex); // Don't pick the same effect twice
	}

	// --- 5. CREATE THE FINAL UPGRADE DATA OBJECT ---
	UPRUpgradeData* FinalOffer = NewObject<UPRUpgradeData>();
	FinalOffer->SourceItemDefinition = ItemDef;
	FinalOffer->DisplayName = ItemDef->DisplayName;
	FinalOffer->Icon = ItemDef->Icon;
	FinalOffer->Description = FText::FromString(FinalDescription);
	FinalOffer->Rarity = RolledRarity;
	FinalOffer->Effects = FinalEffects;
	 
	if (bIsNewItem)
	{
		// If it's a new item, the level is always 1.
		FinalOffer->UpgradeLevel = 1;
	}
	else // It's an upgrade for an existing item
	{
		if (PlayerInventory)
		{
			// Find the existing item in the inventory to get its current level.
			if (const UPRBaseItem* ExistingItem = PlayerInventory->FindItemByDefinition(ItemDef))
			{
				// The upgrade will take it to the NEXT level.
				FinalOffer->UpgradeLevel = ExistingItem->GetCurrentLevel() + 1;

				// We can also make the description more informative here!
				// Example:
				// FString LevelText = FString::Printf(TEXT("LVL %d -> LVL %d\n"), ExistingItem->GetCurrentLevel(), FinalOffer->UpgradeLevel);
				// FinalOffer->Description = FText::FromString(LevelText + FinalOffer->Description.ToString());
			}
			else
			{
				// This case shouldn't happen if our logic is correct, but as a fallback:
				FinalOffer->UpgradeLevel = 1;
			}
		}
		else
		{
			// Fallback if inventory is not valid for some reason.
			FinalOffer->UpgradeLevel = 1;
		}
	}
	return FinalOffer;
}

EUpgradeRarity UPRRewardManager::RollForRarity()
{
	// @TODO: Simple rarity roll. A real system would use weighted probabilities and effected by luck.
	float Roll = FMath::FRand(); // 0.0 to 1.0
	if (Roll < 0.60f) return EUpgradeRarity::Common;     // 60% chance
	if (Roll < 0.85f) return EUpgradeRarity::Uncommon;   // 25% chance
	if (Roll < 0.95f) return EUpgradeRarity::Rare;       // 10% chance
	if (Roll < 0.99f) return EUpgradeRarity::Epic;       // 4% chance
	else return EUpgradeRarity::Legendary;               // 1% chance
}
