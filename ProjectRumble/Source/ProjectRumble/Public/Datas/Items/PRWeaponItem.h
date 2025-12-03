// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRBaseItem.h"
#include "PRWeaponItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageDealtSignature, float, DamageDealt, AActor*, DamagedActor);

class APRCharacterBase;
class APRAIBase;

//Defines the special tags to be earned at a certain level.
USTRUCT(BlueprintType)
struct FLevelMilestone
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelRequired;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag TagToGrant;
};

/**
 * Represents a Weapon item that can perform attacks on a timer.
 */
UCLASS(Blueprintable)
class PROJECTRUMBLE_API UPRWeaponItem : public UPRBaseItem
{
	GENERATED_BODY()
	
public:
	// Override the Initialize function to start the attack timer.
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects) override;

	// Override the LevelUp function to potentially update the timer.
	virtual void LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintAssignable)
	FOnDamageDealtSignature OnDamageDealt;

	// -- PROPERTIES --
	// A list of special abilities granted at specific levels.
	UPROPERTY(EditDefaultsOnly, Category = "Upgrades|Milestones")
	TArray<FLevelMilestone> Milestones;

protected:

	// The timer handle that manages the attack loop.
	FTimerHandle AttackTimerHandle;

	// Local stat modifiers specific to this weapon instance.
	UPROPERTY()
	TMap<FGameplayTag, float> LocalStatModifiers;

	// The function that performs the actual attack logic (spawning projectiles, etc.).
	// This should be overridden by specific weapon Blueprints or C++ classes.
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void ExecuteAttack();

	// The function that is bound to the timer.
	UFUNCTION()
	void Attack();

	// -- Helper Functions for Calculations --
	// A helper function to get the final, calculated cooldown for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedCooldown() const;

	// A helper function to get the final, calculated damage for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedDamage() const;

	// A helper function to get the final, calculated critical hit chance for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedCritChance() const;

	// A helper function to get the final, calculated critical hit damage for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedCritDamage() const;

	// A helper function to get the final, calculated size for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedSize() const;

	// A helper function to get the final, calculated knockback for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedKnockback() const;

	// A helper function to get the final, calculated duration for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedDuration() const;

	// A helper function to get the final, calculated projectile bounce for this weapon.
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	int32 GetCalculatedProjectileBounce() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	int32 GetCalculatedProjectileCount() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedProjectileSpeed() const;

	// Stun chance and duration calculations
	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedStunChance() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedStunDuration() const;

	// This function will now be the central point for all damage calculations.
	// It can be called from Blueprint.
	UFUNCTION(BlueprintCallable, Category = "Weapon|Calculations")
	FDamageCalculationResult CalculateFinalDamage(const APRAIBase* Target);

	/** The list of all effects this weapon instance has applied to the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing = OnRep_AppliedEffects, Category = "Weapon")
	TArray<FPotentialUpgradeEffect> AppliedEffects;

	/** Helper function to apply a list of effects to the owner's StatsComponent. */
	//void ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply);

	UFUNCTION()
	void OnRep_AppliedEffects();

	// Recalculates local stats based on current effects and upgrades.
	void RecalculateLocalStats();

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	FPRWeaponAttackStats GetCalculatedAttackStats() const;
};
