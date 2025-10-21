// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRBaseItem.h"
#include "PRTomeItem.generated.h"

/**
 * Represents a Tome (or any passive item) that grants permanent stat bonuses.
 */
UCLASS()
class PROJECTRUMBLE_API UPRTomeItem : public UPRBaseItem
{
	GENERATED_BODY()
	
public:
	// Override Initialize to apply its passive stat bonuses.
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects) override;

	// Override LevelUp to apply the next level's bonuses.
	virtual void LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects) override;

	// Called by the InventoryComponent when the item is removed (for future use).
	void Uninitialize();

protected:
	// Helper function to apply this item's bonuses to the StatsComponent.
	void ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply);

	UPROPERTY()
	TArray<FPotentialUpgradeEffect> AppliedEffects;

};
