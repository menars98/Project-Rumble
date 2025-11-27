// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "Components/PRInventoryComponent.h"
#include "Net/UnrealNetwork.h"

APRPlayerState::APRPlayerState()
{
    StatsComponent = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));
    InventoryComponent = CreateDefaultSubobject<UPRInventoryComponent>(TEXT("InventoryComponent"));

	SetReplicates(true);
	NetUpdateFrequency = 10.0f;
}

void APRPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	// Only the server should initialize these components.
	if (HasAuthority())
	{
		InitializeStatsComponent();
		InitializeInventoryComponent();

		UE_LOG(LogTemp, Warning, TEXT("[SERVER] PlayerState BeginPlay - Stats initialized"));
	}
}

void APRPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APRPlayerState, StatsComponent);
	DOREPLIFETIME(APRPlayerState, InventoryComponent);
}

void APRPlayerState::OnRep_StatsComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("[CLIENT] StatsComponent replicated"));

	InitializeStatsComponent();
}

void APRPlayerState::OnRep_InventoryComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("[CLIENT] InventoryComponent replicated"));

	InitializeInventoryComponent();
}

void APRPlayerState::InitializeStatsComponent()
{
	if (!StatsComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("StatsComponent is NULL in InitializeStatsComponent!"));
		return;
	}

	// Delegate broadcast (for both server and client)
	if (OnStatsComponentReady.IsBound())
	{
		OnStatsComponentReady.Broadcast(StatsComponent);
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] StatsComponent initialized for PlayerState: %s"),
		HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetName());
}

void APRPlayerState::InitializeInventoryComponent()
{
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InventoryComponent is NULL!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[%s] InventoryComponent initialized for PlayerState: %s"),
		HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetName());
}
