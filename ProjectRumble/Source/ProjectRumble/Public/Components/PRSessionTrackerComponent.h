// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "PRSessionTrackerComponent.generated.h"

// To notify the UI when changes occur, use a delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrackerStatUpdated, FGameplayTag, StatTag, float, NewValue);

USTRUCT(BlueprintType)
struct FTrackedStatContainer
{
    GENERATED_BODY()

    // @TODO: Using TArray for replication is easier than using Map (Fast Array Serialization).
    // But for now, let's create a simple array, as there won't be much data.

    UPROPERTY()
    TArray<float> Values;
    // The easiest way is to keep it on the Server and send an RPC or RepNotify Array to the Client saying “These are my stats.”
};

// Simple Replication Method: Struct Array
USTRUCT(BlueprintType)
struct FReplicatedTrackerData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FGameplayTag Tag;

    UPROPERTY(BlueprintReadOnly)
    float Value;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRUMBLE_API UPRSessionTrackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPRSessionTrackerComponent();

    // Adds a value to a statistic (e.g., +1 Kill, +500 Damage)
    UFUNCTION(BlueprintCallable, Category = "Tracker")
    void AddStat(FGameplayTag StatTag, float Amount);

    UFUNCTION(BlueprintPure, Category = "Tracker")
    float GetStat(FGameplayTag StatTag) const;

	// Event that the UI can listen to
    UPROPERTY(BlueprintAssignable)
    FOnTrackerStatUpdated OnStatUpdated;

    // For the UI to be able to retrieve the entire list
    UFUNCTION(BlueprintPure, Category = "Tracker")
    TArray<FReplicatedTrackerData> GetAllStats() const { return ReplicatedStats; }

    /**
     * Prints all current stats to the Output Log.
     * Useful for debugging without UI.
     */
    UFUNCTION(BlueprintCallable, Category = "Tracker|Debug")
    void DebugLogAllStats();
protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Server-side fast access map
    TMap<FGameplayTag, float> InternalMap;

    // Replicated Array (Clients read this)
    UPROPERTY(ReplicatedUsing = OnRep_Stats)
    TArray<FReplicatedTrackerData> ReplicatedStats;

    UFUNCTION()
    void OnRep_Stats();

    void UpdateReplicatedArray(FGameplayTag Tag, float NewValue);
};
