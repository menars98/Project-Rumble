// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PRSessionTrackerComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"

UPRSessionTrackerComponent::UPRSessionTrackerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UPRSessionTrackerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPRSessionTrackerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPRSessionTrackerComponent, ReplicatedStats);
}

void UPRSessionTrackerComponent::AddStat(FGameplayTag StatTag, float Amount)
{
    if (!GetOwner()->HasAuthority()) return; 

    // 1. Update Map (Fast)
    float& CurrentVal = InternalMap.FindOrAdd(StatTag);
    CurrentVal += Amount;

    // 2. Update array for client
    UpdateReplicatedArray(StatTag, CurrentVal);

    // 3. Send event for server side
    OnStatUpdated.Broadcast(StatTag, CurrentVal);
}

float UPRSessionTrackerComponent::GetStat(FGameplayTag StatTag) const
{
	// If we are client - read from replicated array
    for (const FReplicatedTrackerData& Data : ReplicatedStats)
    {
        if (Data.Tag == StatTag) return Data.Value;
    }
    return 0.0f;
}

void UPRSessionTrackerComponent::UpdateReplicatedArray(FGameplayTag Tag, float NewValue)
{
	// Look for existing entry, if found - update it, if not - add new one
    bool bFound = false;
    for (FReplicatedTrackerData& Data : ReplicatedStats)
    {
        if (Data.Tag == Tag)
        {
            Data.Value = NewValue;
            bFound = true;
            break;
        }
    }

    if (!bFound)
    {
        FReplicatedTrackerData NewData;
        NewData.Tag = Tag;
        NewData.Value = NewValue;
        ReplicatedStats.Add(NewData);
    }
}

void UPRSessionTrackerComponent::OnRep_Stats()
{
    // New data has arrived for the client; we can trigger an event to update the UI
    // Or, the data has simply been updated; the UI will fetch it using GetStat.
}

