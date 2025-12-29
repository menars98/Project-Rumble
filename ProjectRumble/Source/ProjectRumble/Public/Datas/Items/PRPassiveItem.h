// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRBaseItem.h"
#include "PRPassiveItem.generated.h"

/**
 * Represents a Tome (or any passive item) that grants permanent stat bonuses.
 */
UCLASS()
class PROJECTRUMBLE_API UPRPassiveItem : public UPRBaseItem
{
	GENERATED_BODY()
	
public:
	// Override Initialize to apply its passive stat bonuses.
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects) override;

	// Override LevelUp to apply the next level's bonuses.
	virtual void LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects) override;

	// Called by the InventoryComponent when the item is removed (for future use).
	virtual void Deactivate() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	// Scans all history, deletes the old, adds the new.
	void RecalculateAndApplyStats();

	// Helper function to apply this item's bonuses to the StatsComponent.
	//void ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply);

	// The TOTAL bonuses this item currently provides to the player.
	// Key: StatTag, Value: Value Provided (e.g., +15.0)
	TMap<FGameplayTag, float> GrantedBonusesMap;

	UPROPERTY(Replicated)
	TArray<FPotentialUpgradeEffect> AppliedEffects;

};
