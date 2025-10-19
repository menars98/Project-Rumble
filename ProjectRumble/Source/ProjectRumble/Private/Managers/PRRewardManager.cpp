// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRRewardManager.h"
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

		// Pick a random item definition from the pool
		int32 RandomIndex = FMath::RandRange(0, TempItemPool.Num() - 1);
		UPRItemDefinition* ChosenItemDef = TempItemPool[RandomIndex];

		// For now, we assume all offers are level-ups (bIsNewItem = false).
		// TODO: Add logic to check if the player owns the item.
		UPRUpgradeData* NewOffer = CreateUpgradeOfferForItem(ChosenItemDef, false);
		if (NewOffer)
		{
			OfferedRewards.Add(NewOffer);
		}

		// Remove from temp pool to avoid offering the same item twice
		TempItemPool.RemoveAt(RandomIndex);
	}

	return OfferedRewards;
}

UPRUpgradeData* UPRRewardManager::CreateUpgradeOfferForItem(UPRItemDefinition* ItemDef, bool bIsNewItem)
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
	TArray<FUpgradeEffect> FinalEffects;
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
		// We now use the member variable 'StatsInfoTable'
		if (StatsInfoTable)
		{
			// The rest of this logic is the same as before
			for (const FName& RowName : StatsInfoTable->GetRowNames())
			{
				FStatDefinition* StatDef = StatsInfoTable->FindRow<FStatDefinition>(RowName, "");
				if (StatDef && StatDef->StatID == ChosenPotentialEffect.TargetStat)
				{
					StatDisplayName = StatDef->DisplayName.ToString();
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
		FUpgradeEffect FinalEffect;
		FinalEffect.TargetStat = ChosenPotentialEffect.TargetStat;
		FinalEffect.MinMagnitude = RolledMagnitude; // We store the rolled value in both Min and Max
		FinalEffect.MaxMagnitude = RolledMagnitude; // to make it a fixed value.

		FinalEffects.Add(FinalEffect);

		// --- Build the description string based on the operation type ---
		FString TagName = ChosenPotentialEffect.TargetStat.ToString();
		if (TagName.EndsWith(TEXT(".Multiplicative")))
		{
			FinalDescription += FString::Printf(TEXT("%s: +%.1f%%\n"), *StatDisplayName, RolledMagnitude * 100);
		}
		else // Diðer her þey (Additive veya son eki olmayanlar)
		{
			// Additive formatlama
			FinalDescription += FString::Printf(TEXT("%s: +%.0f\n"), *StatDisplayName, RolledMagnitude);
		}

		PotentialEffects.RemoveAt(RandomIndex); // Don't pick the same effect twice
	}

	// --- 5. CREATE THE FINAL UPGRADE DATA OBJECT ---
	UPRUpgradeData* FinalOffer = NewObject<UPRUpgradeData>();
	FinalOffer->DisplayName = ItemDef->DisplayName;
	FinalOffer->SourceItemDefinition = ItemDef;
	FinalOffer->Icon = ItemDef->Icon;
	FinalOffer->Description = FText::FromString(FinalDescription);
	FinalOffer->Rarity = RolledRarity;
	FinalOffer->Effects = FinalEffects;

	// For now, if it's a new item, it's Level 1. If it's an upgrade, we can't know the level yet.
	// Let's default to 1 for now until we have an inventory.
	// TODO: Get the real current level from the InventoryComponent.
	if (bIsNewItem)
	{
		FinalOffer->UpgradeLevel = 1;
	}
	else
	{
		// We don't know the "from -> to" level yet. Let's just put the player's level for now as a placeholder.
		// A proper implementation needs the InventoryComponent.
		FinalOffer->UpgradeLevel = 1; // Placeholder
	}
	return FinalOffer;
}

EUpgradeRarity UPRRewardManager::RollForRarity()
{
	// Simple rarity roll. A real system would use weighted probabilities and effected by luck.
	float Roll = FMath::FRand(); // 0.0 to 1.0
	if (Roll < 0.60f) return EUpgradeRarity::Common;     // 60% chance
	if (Roll < 0.85f) return EUpgradeRarity::Uncommon;   // 25% chance
	if (Roll < 0.95f) return EUpgradeRarity::Rare;       // 10% chance
	if (Roll < 0.99f) return EUpgradeRarity::Epic;       // 4% chance
	else return EUpgradeRarity::Legendary;               // 1% chance
}
