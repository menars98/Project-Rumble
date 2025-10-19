// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRBaseItem.h"
#include "PRWeaponItem.generated.h"

class APRCharacterBase;

/**
 * Represents a Weapon item that can perform attacks on a timer.
 */
UCLASS(Blueprintable)
class PROJECTRUMBLE_API UPRWeaponItem : public UPRBaseItem
{
	GENERATED_BODY()
	
public:
	// Override the Initialize function to start the attack timer.
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FUpgradeEffect>& InitialEffects) override;

	// Override the LevelUp function to potentially update the timer.
	virtual void LevelUp() override;

protected:
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

	// The timer handle that manages the attack loop.
	FTimerHandle AttackTimerHandle;

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	int32 GetCalculatedProjectileCount() const;

	UFUNCTION(BlueprintPure, Category = "Weapon|Calculations")
	float GetCalculatedProjectileSpeed() const;

};
