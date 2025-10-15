// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h" 
#include "PRTypes.h"
#include "PRStatsComponent.generated.h"

// This delegate will broadcast when any stat changes, sending the StatTag and its new value.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChangedSignature, FGameplayTag, StatTag, float, NewValue);

// This delegate will broadcast when XP changes, sending the current and max XP.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPChangedSignature, float, CurrentXP, float, MaxXP);

// This delegate will broadcast when health changes, sending the current and max health.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, CurrentHealth, float, MaxHealth);

// This delegate will broadcast when the owner's health reaches zero.
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

// This delegate will broadcast when the owner levels up, sending the new level.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpSignature, int32, NewLevel);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRUMBLE_API UPRStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPRStatsComponent();

	// --- DELEGATES ---
	// Other classes can bind to this delegate to be notified when health changes.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChangedDelegate;

	// Other classes can bind to this to be notified when the owner dies.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathSignature OnDeathDelegate;

	// Other classes can bind to this to be notified when the owner levels up.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLevelUpSignature OnLevelUpDelegate;

	// Other classes can bind to this to be notified when XP changes.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnXPChangedSignature OnXPChangedDelegate;

	// Other classes can bind to this to be notified when any stat changes.
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStatChangedSignature OnStatChangedDelegate;

	// --- PUBLIC FUNCTIONS ---
	/**
	 * Gets the current value of a specified stat.
	 * @param StatID The FName ID of the stat to retrieve (e.g., "Health").
	 * @return The current float value of the stat. Returns 0 if stat is not found.
	 */
	UFUNCTION(BlueprintPure, Category = "PR | Stats")
	float GetStatValue(FGameplayTag  StatTag) const;
	/**
	 * Internal function to set the value of a stat directly.
	* @param StatID The ID of the stat to change.
	* @param NewValue The new value for the stat.
	*/
	UFUNCTION(BlueprintCallable, Category = "PR | Stats")
	void SetStatValue(FGameplayTag  StatTag, float NewValue);
	/**
	 * Applies damage to the owner of this component. Automatically handles health reduction and death.
	 * @param DamageAmount The amount of damage to apply.
	 */
	UFUNCTION(BlueprintCallable, Category = "PR | Stats")
	void ApplyDamage(float DamageAmount);

	void InitializeWithDataTable(UDataTable* DataTableToUse);

	UFUNCTION(BlueprintCallable, Category = "PR | Stats")
	void AddXP(float XPAmount);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Reads the StatsDataTable and populates the CurrentStats map with default values.
	 * This is the core initialization function for the component.
	 */
	void InitializeStats();

	/**
	 * Handles the death of the owner. Broadcasts the OnDeathDelegate.
	 */
	UFUNCTION() // @TODO UFUNCTION macro is needed if this will be bound to a timer or another delegate later.
	void Die();

private:
	// --- PRIVATE PROPERTIES ---
	// The Data Table that defines all possible stats and their default values.
	// This should be assigned in the Blueprint derived from this component.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> StatsDataTable;

	// A map that holds the RUNTIME values of all stats.
	// FName is the StatID (e.g., "Health"), float is the current value.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, float> CurrentStats;

	// --- PRIVATE FUNCTIONS ---

	/**
	 * A helper function to easily broadcast the OnHealthChangedDelegate with current values.
	 */
	void BroadcastHealth();
};
