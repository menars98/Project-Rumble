// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "Components/PRInventoryComponent.h"

APRPlayerState::APRPlayerState()
{
    StatsComponent = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));
    InventoryComponent = CreateDefaultSubobject<UPRInventoryComponent>(TEXT("InventoryComponent"));
}

void APRPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// By the time the PlayerState's BeginPlay is called, its components are guaranteed to be created.
	if (StatsComponent && OnStatsComponentReady.IsBound())
	{
		OnStatsComponentReady.Broadcast(StatsComponent);
	}
}
