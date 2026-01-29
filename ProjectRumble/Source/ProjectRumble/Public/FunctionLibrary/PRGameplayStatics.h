// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Datas/Items/PRWeaponItem.h"
#include "AssetRegistry/AssetRegistryModule.h" 
#include "GameplayTagsManager.h"
#include "PRTypes.h" 
#include "PRGameplayStatics.generated.h"

class APRAIBase;
class UPRStatsComponent;
class USoundBase;

UENUM(BlueprintType)
enum class ERowResult : uint8
{
	Found,
	NotFound
};

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
	 * @param WorldContextObject The context object for world access.
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
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "ProjectRumble|Damage")
	static float ApplyRumbleDamage(
		UObject* WorldContextObject,
		AActor* DamagedActor,
		float BaseDamage,
		const FDamageCalculationResult& DamageResult,
		FGameplayTag DamageSourceTag,
		AController* EventInstigator,
		AActor* DamageCauser,
		TSubclassOf<class UDamageType> DamageTypeClass,
		const FVector& KnockbackDirection,
		float KnockbackMagnitude,
		float StunChance,
		float StunDuration,
		USoundBase* HitSound = nullptr
	);

	/**
	* Performs a sphere overlap, scales radius by attacker's Size stat,
	* calculates damage (crit etc.), and applies it to all found enemies.
	* @param WorldContextObject The context object for world access.
	* @param Attacker The actor dealing the damage (Player/AI).
	* @param Origin The center point of the explosion.
	* @param BaseRadius The base radius of the explosion.
	* @param BaseDamage The base damage of the explosion.
	* @param CritChance The critical hit chance of the weapon/item.
	* @param CritMultiplier The critical hit damage multiplier of the weapon/item.
	* @param KnockbackStrength The strength of the knockback effect.
	* @param DamageSourceTag The tag representing the source item (for tracking).
	* @param bDrawDebug Whether to draw debug visuals for the overlap.
	*/
	UFUNCTION(BlueprintCallable, Category = "Rumble|Combat", meta = (WorldContext = "WorldContextObject"))
	static void ApplyRadialRumbleDamage(
		UObject* WorldContextObject,
		AActor* Attacker,              
		FVector Origin,                
		float BaseRadius,              
		float BaseDamage,              
		float CritChance,              
		float CritMultiplier,          
		float KnockbackStrength,       
		FGameplayTag DamageSourceTag,  
		bool bDrawDebug = false        
	);

	/**
	 * Finds enemies in radius, picks 'NumTargets' random victims, and deals damage.
	 * Good for mechanics like "Static Discharge" or "Lightning Strikes".
	 * @param WorldContextObject The context object for world access.
	 * @param Attacker The actor dealing the damage (Player/AI).
	 * @param Origin The center point of the effect.
	 * @param BaseRadius The base radius to search for targets.
	 * @param BaseDamage The base damage to apply to each target.
	 * @param NumTargets The number of random targets to hit.
	 * @param DamageSourceTag The tag representing the source item (for tracking).
	 */
	UFUNCTION(BlueprintCallable, Category = "Rumble|Combat", meta = (WorldContext = "WorldContextObject"))
	static AActor* ApplyRandomRumbleDamage( 
		UObject* WorldContextObject,
		AActor* Attacker,
		FVector Origin,
		float BaseRadius,
		float BaseDamage,
		int32 NumTargets,              
		FGameplayTag DamageSourceTag
	);

	/**
	 * Sorts an array of actors by their distance to a target location.
	 * @param TargetLocation The origin point to measure distance from.
	 * @param ActorsToSort The array of actors to be sorted.
	 * @return A new array of actors, sorted from nearest to farthest.
	 */
	UFUNCTION(BlueprintPure, Category = "ProjectRumble|Utilities")
	static TArray<AActor*> SortActorsByDistance(const FVector& TargetLocation, const TArray<AActor*>& ActorsToSort);

	/**
	 * Spawns floating damage numbers above a target actor.
	 * @param Damage The amount of damage to display.
	 * @param bIsCrit Whether the damage was a critical hit.
	 * @param TargetActor The actor above which to spawn the damage number.
	 * @param PlayerController The player controller for UI context.
	 */
	UFUNCTION(BlueprintCallable, Category = "UI")
	static void SpawnDamageNumber(UObject* WorldContextObject, float Damage, bool bIsCrit, AActor* TargetActor, FGameplayTag DamageTag);

	/**
	* Searches for a tag in the Data Table and returns the Row data directly.
	* @param DataTable The table to be scanned.
	* @param TagToFind The tag to be searched for.
	* @param OutRow (Wildcard) The found row data is copied here.
	*/
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Rumble|Data", meta = (CustomStructureParam = "OutRow", ExpandEnumAsExecs = "OutResult"))
	static void GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag TagToFind, int32& OutRow, ERowResult& OutResult);

	// We are defining the “exec” function required for CustomThunk.
	DECLARE_FUNCTION(execGetDataTableRowByTag);

	/**
	* Checks if a specific Key is mapped to a specific Input Action for the given Player.
	* Useful for UI to detect "Action" presses dynamically.
	*/
	UFUNCTION(BlueprintPure, Category = "Rumble|Input", meta = (WorldContext = "WorldContextObject"))
	static bool IsKeyMappedToAction(UObject* WorldContextObject, FKey Key, const UInputAction* Action);

	/**
    * Checks if the game viewport currently has operating system focus.
    * Useful for detecting Alt-Tab.
    */
	UFUNCTION(BlueprintPure, Category = "Rumble|System")
	static bool IsGameWindowFocused();

	/**
	* Finds all Data Assets derived from a specific class in the project.
	* Example: Get all UPRPassiveItemDefinition instances.
	*/
	UFUNCTION(BlueprintCallable, Category = "Editor Tools")
	static TArray<FAssetData> FindAllAssetsOfClass(UClass* BaseClass);

	/**
	 * Editor Only: Adds a new row to the Loot Table for the given item.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor Tools")
	static void AddMissingItemToLootTable(UDataTable* DataTable, UPRItemDefinition* ItemDef, float DefaultWeight = 1.0f);

	static float GetActorStatValue(AActor* Actor, FGameplayTag StatTag);

	/**
	* Editor Only: Retrieves tags under a specific Parent Tag.
     * @param bOnlyLeaves If true, does not retrieve tags that have other tags under them (i.e., category tags).
	*/
	UFUNCTION(BlueprintCallable, Category = "Editor Tools")
	static TArray<FGameplayTag> GetAllTagsUnderParent(FGameplayTag ParentTag, bool bOnlyLeaves = true);

	/**
	 * Editor Only: Adds the missing stat to the stat table.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor Tools")
	static void AddMissingStatToTable(UDataTable* DataTable, FGameplayTag StatTag);

protected:

	/**
	* Calculates the knockback force vector based on attacker and victim positions.
	*/
	static FVector CalculateDynamicKnockback(AActor* Attacker, AActor* Victim);

	/**
	 * Applies the final knockback force to the victim actor.
	 */
	static void ApplyFinalKnockback(AActor* Victim, FVector Force);
};
