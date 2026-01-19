// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRBaseItem.h"
#include "PRPassiveItem.generated.h"

class UPRPassiveItemDefinition;
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

	 // --- EVENT HOOKS ---

	UFUNCTION(BlueprintImplementableEvent, Category = "Item Logic", meta = (DisplayName = "On Initialize"))
	void ReceiveInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "Item Logic")
	void ExecutePassiveAbility();

	/**
	* The event Blueprint will use.
	* If the Item overrides this event, it will run automatically when XP is earned.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Item Logic")
	void OnXPGained(float Amount, float NewTotalXP);

	// -- END --
	
	void StartAbilityTimer(float Cooldown);

	void TriggerAbility();

	FTimerHandle AbilityTimerHandle;

	// The TOTAL bonuses this item currently provides to the player.
	// Key: StatTag, Value: Value Provided (e.g., +15.0)
	TMap<FGameplayTag, float> GrantedBonusesMap;

	UPROPERTY(Replicated)
	TArray<FPotentialUpgradeEffect> AppliedEffects;

	UPROPERTY(BlueprintReadOnly, Category = "Item")
	const UPRPassiveItemDefinition* PassiveDefinition;

private:
	// Delegate
	UFUNCTION()
	void HandleXPChanged(float CurrentXP, float MaxXP);

	// Let's keep the old XP so we can calculate the “Amount” (How much did we earn?).
	float LastKnownXP = 0.0f;
};
