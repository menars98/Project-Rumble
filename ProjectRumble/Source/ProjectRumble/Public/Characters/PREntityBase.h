// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PRTypes.h" 
#include "PREntityBase.generated.h"

class UPRStatsComponent;


UCLASS()
class PROJECTRUMBLE_API APREntityBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APREntityBase();

	// A public getter to allow other classes to easily access the Stats Component.
	UFUNCTION(BlueprintPure, Category = "PR | Components")
	virtual UPRStatsComponent* GetStatsComponent() const;

	// A public getter for the entity's faction.
	UFUNCTION(BlueprintPure, Category = "PR | Combat")
	EFaction GetFaction() const { return Faction; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override the default TakeDamage function from AActor.
	// This will be the main entry point for all damage taken by this entity.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// This function is bound to the OnHealthChangedDelegate from our StatsComponent.
	// It will be called automatically whenever health changes.
	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth, float MaxHealth);

	// This function is bound to the OnDeathDelegate from our StatsComponent.
	// It's virtual so that child classes (like Player and AI) can have different death behaviors.
	UFUNCTION()
	virtual void OnDeath();

	// -- COMBAT --
	// This entity's faction. Should be set in the derived Blueprint classes.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	EFaction Faction;

	// --- DAMAGE PROCESSING HELPER FUNCTIONS ---

	/**
	 * Checks if the incoming attack should be evaded based on the Evasion stat.
	 * @param StatsComponent The stats component to read the Evasion stat from.
	 * @return True if the attack was successfully evaded.
	 */
	UFUNCTION(BlueprintPure, Category = "Combat|Defense")
	bool CheckForEvasion(const UPRStatsComponent* StatsComponent) const;

	/**
	 * Calculates the final damage after applying Armor reduction.
	 * @param InitialDamage The damage amount before armor is applied.
	 * @param StatsComponent The stats component to read the Armor stat from.
	 * @return The final damage amount to be applied.
	 */
	UFUNCTION(BlueprintPure, Category = "Combat|Defense")
	float CalculateArmorReduction(float InitialDamage, const UPRStatsComponent* StatsComponent) const;

	/**
	 * Applies Thorns damage back to the attacker.
	 * @param StatsComponent The stats component to read the Thorns stat from.
	 * @param DamageCauser The actor that caused the initial damage.
	 */
	UFUNCTION(BlueprintCallable, Category = "Combat|Defense")
	void ApplyThornsDamage(const UPRStatsComponent* StatsComponent, AActor* DamageCauser);

	/**
	 * Processes incoming damage against the shield.
	 * Absorbs damage with the shield and returns any remaining damage.
	 * Also triggers the shield regeneration delay.
	 * @param InitialDamage The damage amount before shield absorption.
	 * @param StatsComponent The stats component to read/write shield values from.
	 * @return The amount of damage that was NOT absorbed by the shield.
	 */
	UFUNCTION(BlueprintPure, Category = "Combat|Defense")
	float ProcessShieldDamage(float InitialDamage, UPRStatsComponent* StatsComponent);

};
