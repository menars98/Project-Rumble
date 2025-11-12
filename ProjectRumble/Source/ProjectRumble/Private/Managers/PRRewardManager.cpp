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
	TArray<UPRItemDefinition*> TempItemPool;

	// Get current counts by directly accessing the array size.
	int32 CurrentWeaponCount = PlayerInventory->GetWeaponCount();
	int32 CurrentTomeCount = PlayerInventory->GetTomeCount();

	// Get limits by directly accessing the variables.
	const int32 MaxWeapons = PlayerInventory->GetMaxWeaponCount();
	const int32 MaxTomes = PlayerInventory->GetMaxTomeCount();

	// --- 1. BUILD A POOL OF RELEVANT ITEMS ---
	for (UPRItemDefinition* ItemDef : AllPossibleItems)
	{
		if (!ItemDef) continue;

		// Check if the item is already owned (using the existing helper function)
		bool bIsOwned = PlayerInventory->FindItemByDefinition(ItemDef) != nullptr;

		// Rule A: Always offer UPGRADES for OWNED items.
		if (bIsOwned)
		{
			TempItemPool.Add(ItemDef);
			continue; 
		}

		// Rule B: Offer NEW items only if there is space (Weapon/Tome limit check).
		EItemType ItemType = ItemDef->ItemType;

		if (ItemType == EItemType::Weapon && CurrentWeaponCount < MaxWeapons)
		{
			TempItemPool.Add(ItemDef);
		}
		else if (ItemType == EItemType::Tome && CurrentTomeCount < MaxTomes)
		{
			TempItemPool.Add(ItemDef);
		}
		// Note: Relics and other types will be ignored if their limits aren't checked here.
	}

	// --- 2. GENERATE REWARDS FROM THE FILTERED POOL ---
	for (int32 i = 0; i < NumOfChoices; ++i)
	{
		if (TempItemPool.Num() == 0) break;

		int32 RandomIndex = FMath::RandRange(0, TempItemPool.Num() - 1);
		UPRItemDefinition* ChosenItemDef = TempItemPool[RandomIndex];
		
		// Determine if it's a new item (Check the inventory here, NOT the filter logic!)
		bool bIsNewItemOffer = PlayerInventory->FindItemByDefinition(ChosenItemDef) == nullptr;

		// Create the offer and add to rewards.
		UPRUpgradeData* NewOffer = CreateUpgradeOfferForItem(ChosenItemDef, PlayerInventory, bIsNewItemOffer);
		if (NewOffer)
		{
			OfferedRewards.Add(NewOffer);
		}

		// Remove the item from the pool so it cannot be chosen again in this same screen instance.
		TempItemPool.RemoveAt(RandomIndex);
	}

	return OfferedRewards;
}

// Generate loot rewards from a Loot Table its for item not tomes or weapons
TArray<UPRUpgradeData*> UPRRewardManager::GenerateLootRewards(const UPRInventoryComponent* PlayerInventory, UDataTable* LootTable, int32 NumToAward)
{
	TArray<UPRUpgradeData*> LootRewards;
	if (!LootTable) return LootRewards;

	// 1. Get all valid rows from the Loot Table
	TArray<FLootTableRow*> PossibleLoot;
	float TotalWeight = 0.f;
	FString ContextString;
	for (FName RowName : LootTable->GetRowNames())
	{
		if (FLootTableRow* Row = LootTable->FindRow<FLootTableRow>(RowName, ContextString))
		{
			if (Row->ItemDefinition)
			{
				PossibleLoot.Add(Row);
				TotalWeight += Row->Weight;
			}
		}
	}

	// 2. Draft items based on weight
	for (int32 i = 0; i < NumToAward; ++i)
	{
		if (PossibleLoot.Num() == 0 || TotalWeight <= 0.f) break;

		float RandomValue = FMath::FRandRange(0.f, TotalWeight);
		float CurrentWeight = 0.f;

		for (int32 j = 0; j < PossibleLoot.Num(); ++j)
		{
			CurrentWeight += PossibleLoot[j]->Weight;
			if (RandomValue <= CurrentWeight)
			{
				// FOUND THE WINNER!
				FLootTableRow* SelectedRow = PossibleLoot[j];

				// Check if it's a new item or an upgrade for the player
				bool bIsNewItem = true;
				if (PlayerInventory && PlayerInventory->FindItemByDefinition(SelectedRow->ItemDefinition))
				{
					bIsNewItem = false;
				}

				// Create the upgrade data offer
				UPRUpgradeData* LootOffer = CreateUpgradeOfferForItem(SelectedRow->ItemDefinition, PlayerInventory, bIsNewItem);
				if (LootOffer)
				{
					LootRewards.Add(LootOffer);
				}

				// Optional: Don't drop the same item twice in one chest?
				// If so, remove from PossibleLoot and subtract weight.
				// For now, let's allow duplicates (e.g. getting 2x Gold Coins).
				break;
			}
		}
	}

	return LootRewards;
}

UPRUpgradeData* UPRRewardManager::CreateUpgradeOfferForItem(UPRItemDefinition* ItemDef, const UPRInventoryComponent* PlayerInventory, bool bIsNewItem)
{
	if (!ItemDef) return nullptr;

	// --- 1. ROLL FOR RARITY ---
	EUpgradeRarity RolledRarity = RollForRarity(50);

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
		}
	}
	return FinalOffer;
}

EUpgradeRarity UPRRewardManager::RollForRarity(float PlayerLuck) const
{
	// --- 1. BASE WEIGHTS (Sum to 100.0f) ---
	// Static weights for 0 Luck.
	const float W_L_BASE = 1.0f;
	const float W_E_BASE = 4.0f;
	const float W_R_BASE = 10.0f;
	const float W_UC_BASE = 15.0f;
	const float W_C_BASE = 70.0f;
	const float RARE_POOL_BASE_TOTAL = W_L_BASE + W_E_BASE + W_R_BASE; // 15.0f

	// Scale PlayerLuck: 100% Luck = 1.0f. 4000% Luck = 40.0f.
	const float ScaledLuck = PlayerLuck / 100.0f;

	// --- 2. EXPONENTIAL DECAY (Shrinking the Lower Tiers) ---
	// The core of the dynamic system: Agreesive drop that slows down (e^-kx curve).

	// Common Decay Rate (k_c = 0.06f): Still low but a little faster decay.
	const float K_COMMON = 0.06f;
	// Uncommon Decay Rate (k_uc = 0.04f): A much slower decay for the second tier.
	const float K_UNCOMMON = 0.04f;

	// Current Common Weight: W_C_BASE * e^(-k_c * ScaledLuck)
	float CurrentW_C = W_C_BASE * FMath::Exp(-K_COMMON * ScaledLuck);

	// Current Uncommon Weight: W_UC_BASE * e^(-k_uc * ScaledLuck)
	float CurrentW_UC = W_UC_BASE * FMath::Exp(-K_UNCOMMON * ScaledLuck);

	// Total weight SHIFTED from the lower tiers.
	float TotalShiftAmount = (W_C_BASE - CurrentW_C) + (W_UC_BASE - CurrentW_UC);


	// --- 3. GAIN CALCULATION (Growing the Upper Tiers) ---

	// The shifted weight is initially distributed across RARE, EPIC, and LEGENDARY proportionally.
	// The total gain pool base is 15.0f (RarePoolTotal).
	float W_L_GAIN = TotalShiftAmount * (W_L_BASE / RARE_POOL_BASE_TOTAL);
	float W_E_GAIN = TotalShiftAmount * (W_E_BASE / RARE_POOL_BASE_TOTAL);
	float W_R_GAIN = TotalShiftAmount * (W_R_BASE / RARE_POOL_BASE_TOTAL);

	// --- 4. CONDITIONAL LEGENDARY BOOST (The Late-Game Power) ---
	const float LEGENDARY_BOOST_THRESHOLD = 10.0f; // 1000% Luck threshold.

	if (ScaledLuck >= LEGENDARY_BOOST_THRESHOLD)
	{
		// Calculate the excess luck above the threshold.
		float OverThresholdLuck = ScaledLuck - LEGENDARY_BOOST_THRESHOLD;

		// Add an extra proportional bonus to Legendary based on excess luck.
		// This is a powerful late-game linear boost. (e.g., 5% extra Legendary chance per point of excess luck)
		float Bonus_L = OverThresholdLuck * 0.50f; // 0.5f = 50% increase per point of ScaledLuck.

		W_L_GAIN += Bonus_L;
	}

	// --- 5. FINAL WEIGHTS AND TOTAL ---

	float FinalW_L = W_L_BASE + W_L_GAIN;
	float FinalW_E = W_E_BASE + W_E_GAIN;
	float FinalW_R = W_R_BASE + W_R_GAIN;
	float FinalW_UC = CurrentW_UC;
	float FinalW_C = CurrentW_C;

	float TotalWeight = FinalW_L + FinalW_E + FinalW_R + FinalW_UC + FinalW_C;

	// --- 6.(ROLL) ---

	float Roll = FMath::FRandRange(0.0f, TotalWeight);
	float CurrentThreshold = 0.0f;

	// 1. Common Check
	CurrentThreshold += FinalW_C;
	if (Roll <= CurrentThreshold) return EUpgradeRarity::Common;

	// 2. Uncommon Check
	CurrentThreshold += FinalW_UC;
	if (Roll <= CurrentThreshold) return EUpgradeRarity::Uncommon;

	// 3. Rare Check
	CurrentThreshold += FinalW_R;
	if (Roll <= CurrentThreshold) return EUpgradeRarity::Rare;

	// 4. Epic Check
	CurrentThreshold += FinalW_E;
	if (Roll <= CurrentThreshold) return EUpgradeRarity::Epic;

	// 5. Legendary Check (Everything remaining)
	return EUpgradeRarity::Legendary;
}

