// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/DataAsset.h"
#include "PRCharacterDefinition.generated.h"

// Forward declarations for asset types to reduce compile times
class USkeletalMesh;
class UAnimBlueprint;
class UAnimInstance; // We will use UAnimInstance for the AnimBlueprintClass property
class UTexture2D;
//class UPRBaseWeapon; // Assuming we'll have a base weapon class
//class UPRBasePassiveItem; // Assuming we'll have a base passive item class

/**
 * Data Asset that defines the properties for a playable character.
 * This holds all static, unchanging data for a character like its mesh, stats, and abilities.
 */

UCLASS()
class PROJECTRUMBLE_API UPRCharacterDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:

	// -- VISUALS --
	/** The unique name of this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	FText CharacterName;

	/** A brief description of the character for the selection screen. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals", meta = (MultiLine = true))
	FText CharacterDescription;

	/** The skeletal mesh to use for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	TObjectPtr<USkeletalMesh> CharacterMesh;

	/** The animation blueprint class to use for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	TSubclassOf<UAnimInstance> AnimationBlueprintClass; // Use TSubclassOf<UAnimInstance> for Anim Blueprints

	/** The icon displayed for this character in UI. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	TObjectPtr<UTexture2D> CharacterIcon;

	// -- STATS & ABILITIES --
	/** The Data Table containing the initial stat values for this character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats")
	TObjectPtr<UDataTable> StartingStatsTable;

	/** The primary active ability class for this character (e.g., Ground Slam, Dash). */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	//TSubclassOf<UObject> PrimaryAbilityClass; // UObject for now, can be a custom UAbility class later

	/** The weapon class this character starts with. */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	//TSubclassOf<UPRBaseWeapon> StartingWeaponClass;

	/** The passive item class this character starts with. */
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loadout")
	//TSubclassOf<UPRBasePassiveItem> StartingPassiveItemClass;

	// -- OTHER --
	// (WE can add any other character-specific data here later)
};
