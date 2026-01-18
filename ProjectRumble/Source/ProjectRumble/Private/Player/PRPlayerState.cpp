// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "Components/PRInventoryComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/PRSessionTrackerComponent.h"

APRPlayerState::APRPlayerState()
{
    StatsComponent = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));
    InventoryComponent = CreateDefaultSubobject<UPRInventoryComponent>(TEXT("InventoryComponent"));
	TrackerComponent = CreateDefaultSubobject<UPRSessionTrackerComponent>(TEXT("TrackerComponent"));

	SetReplicates(true);
	SetNetUpdateFrequency(10.0f);
}

void APRPlayerState::SetIsReady(bool bReady)
{
	if (HasAuthority())
	{
		bIsReady = bReady;
	}
	else
	{
		// If not the server, send a request to the server to change the ready status.
		Server_SetIsReady(bReady);
	}
}

void APRPlayerState::SetKillerInfo(FText Name, FGameplayTag Tag)
{
	if (HasAuthority())
	{
		KillerName = Name;
		KillerTag = Tag;

		UE_LOG(LogTemp, Warning, TEXT("Player killed by: %s"), *Name.ToString());
	}
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
	DOREPLIFETIME(APRPlayerState, bIsReady);
	DOREPLIFETIME(APRPlayerState, KillerName);
	DOREPLIFETIME(APRPlayerState, KillerTag);
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

void APRPlayerState::Server_SetIsReady_Implementation(bool bReady)
{
	bIsReady = bReady;
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
