// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Datas/Items/PRWeaponItem.h"
#include "PRGameplayStatics.generated.h"

class APRAIBase;
class UPRStatsComponent;

UCLASS()
class PROJECTRUMBLE_API UPRGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * Calculates the final damage output based on the attacker's stats and the target's properties.
	 * This is the central function for all damage calculations in the game.
	 * @param AttackerStats The StatsComponent of the entity dealing damage (e.g., the player).
	 * @param BaseDamage The weapon's base damage for this attack.
	 * @param BaseCritChance The weapon's base critical hit chance.
	 * @param BaseCritMultiplier The weapon's base critical damage multiplier.
	 * @param Target The AI character being targeted.
	 * @return A struct containing the final damage and whether it was a critical hit.
	 */
	UFUNCTION(BlueprintPure, Category = "ProjectRumble|Damage")
	static FDamageCalculationResult CalculateFinalDamage(
		const UPRStatsComponent* AttackerStats,
		float BaseDamage,
		float BaseCritChance,
		float BaseCritMultiplier,
		const APRAIBase* Target
	);

	/**
	 * Applies damage to a damaged actor, considering knockback effects.
	 * This function wraps around the standard ApplyDamage to include knockback logic.
	 * @param DamagedActor The actor receiving damage.
	 * @param BaseDamage The amount of damage to apply.
	 * @param EventInstigator The controller responsible for the damage.
	 * @param DamageCauser The actor that caused the damage.
	 * @param DamageTypeClass The type of damage being applied.
	 * @param KnockbackDirection The direction vector for knockback.
	 * @param KnockbackMagnitude The strength of the knockback effect.
	 * @param StunDuration The duration of stun to apply (if any).
	 * @return The actual damage applied after all calculations.
	 */ 
	UFUNCTION(BlueprintCallable, Category = "ProjectRumble|Damage")
	static float ApplyRumbleDamage(
		AActor* DamagedActor,
		float BaseDamage,
		AController* EventInstigator,
		AActor* DamageCauser,
		TSubclassOf<class UDamageType> DamageTypeClass,
		const FVector& KnockbackDirection,
		float KnockbackMagnitude,
		float StunChance,
		float StunDuration
	);

	/**
	 * Sorts an array of actors by their distance to a target location.
	 * @param TargetLocation The origin point to measure distance from.
	 * @param ActorsToSort The array of actors to be sorted.
	 * @return A new array of actors, sorted from nearest to farthest.
	 */
	UFUNCTION(BlueprintPure, Category = "ProjectRumble|Utilities")
	static TArray<AActor*> SortActorsByDistance(const FVector& TargetLocation, const TArray<AActor*>& ActorsToSort);
};
