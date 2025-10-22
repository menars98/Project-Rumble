// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PRTypes.h"
#include "PRInventoryComponent.generated.h"

class UPRBaseItem;
class UPRUpgradeData;
class UPRItemDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRUMBLE_API UPRInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPRInventoryComponent();

	/**
	 * The main entry point for applying a chosen reward.
	 * It checks if the item is new or an upgrade and calls the appropriate function.
	 * @param ChosenUpgrade The dynamically generated upgrade data from the RewardManager.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddOrUpgradeItem(UPRUpgradeData* ChosenUpgrade);

	/**
	 * Checks if an item with the given definition already exists in the inventory.
	 * @param ItemDef The item definition to check for.
	 * @return The UPRBaseItem instance if found, otherwise nullptr.
	 */
	UFUNCTION(BlueprintPure, Category = "Inventory")
	UPRBaseItem* FindItemByDefinition(const UPRItemDefinition* ItemDef) const;

	// -- DELEGATES --
	// Broadcasts whenever the inventory changes (item added or upgraded).
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdatedSignature OnInventoryUpdated;

	void AddStartingItem(UPRItemDefinition* ItemDef);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Adds a new item to the inventory based on its definition. */
	void AddNewItem(UPRItemDefinition* ItemDef, const TArray<FPotentialUpgradeEffect>& InitialEffects);

	/** Finds an existing item in the inventory and calls its LevelUp function. */
	void UpgradeExistingItem(UPRBaseItem* ItemToUpgrade, const TArray<FPotentialUpgradeEffect>& UpgradeEffects);

	// The list of all WEAPONS the player currently owns.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<UPRBaseItem>> OwnedWeapons;

	// The list of all TOMES the player currently owns.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<UPRBaseItem>> OwnedTomes;

	// The list of all RELICS the player currently owns.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<UPRBaseItem>> OwnedRelics;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<TObjectPtr<UPRBaseItem>> OwnedItems;

	// Maximum number of items of each type the player can hold.
	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Limits")
	int32 MaxWeapons = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Limits")
	int32 MaxTomes = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory|Limits")
	int32 MaxRelics = 4;
		
};
