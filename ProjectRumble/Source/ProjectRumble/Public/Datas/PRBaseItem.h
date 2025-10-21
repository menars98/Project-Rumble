// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PRTypes.h"
#include "PRBaseItem.generated.h"

class UPRItemDefinition;
class AActor;

/**
 * The base class for all acquirable items in the game (Weapons, Tomes, Relics).
 * This is a UObject, meaning it does not exist in the world physically by itself.
 * It lives inside the InventoryComponent and holds the state of a specific item instance.
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTRUMBLE_API UPRBaseItem : public UObject
{
	GENERATED_BODY()
	
public:

	UPRBaseItem();

	/**
	 * Initializes the item with its static data and owning actor.
	 * This is called by the InventoryComponent when the item is first created.
	 * @param InItemDefinition The Data Asset that defines this item.
	 * @param InOwningActor The actor (usually the player character) that owns this item.
	 * @param InitialEffects The initial upgrade effects to apply to this item.
	 */
	virtual void Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects);


	/**
	 * Levels up the item. This function can be overridden by child classes
	 * to apply specific level-up logic.
	 * @param UpgradeEffects The upgrade effects to apply on level up.
	 */
	virtual void LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects);

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual UWorld* GetWorld() const override;

	// -- GETTERS --

	UFUNCTION(BlueprintPure, Category = "Item")
	int32 GetCurrentLevel() const { return CurrentLevel; }

	UFUNCTION(BlueprintPure, Category = "Item")
	UPRItemDefinition* GetItemDefinition() const { return ItemDefinition; }

protected:
	// The static data that defines what this item is.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UPRItemDefinition> ItemDefinition;

	// The current level of this specific item instance.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	int32 CurrentLevel;

	// A reference to the actor that owns this item (usually the player character).
	// This is useful for getting access to the world, other components, etc.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<AActor> OwningActor;
};
