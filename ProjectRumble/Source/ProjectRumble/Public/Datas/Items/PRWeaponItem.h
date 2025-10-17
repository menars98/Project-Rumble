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
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor) override;

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

	// A helper function to get the final, calculated cooldown for this weapon.
	float GetCalculatedCooldown() const;

	// The timer handle that manages the attack loop.
	FTimerHandle AttackTimerHandle;

};
