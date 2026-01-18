// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PRXpShard.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"
#include "Actors/PRPickupBase.h"
#include "Game/PRGameState.h" 

APRXpShard::APRXpShard()
{
	PrimaryActorTick.bCanEverTick = true; 

	// Create basic components
	//DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent = DefaultSceneRoot;
	// TODO: Create StaticMesh and SphereCollision components here

}

void APRXpShard::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("XPShard Ready!"));
}

void APRXpShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APRXpShard::OnCollected_Implementation()
{
	// Security Check
	if (!HasAuthority())
	{
		return;
	}

	// Call the parent's function first (good practice)
	Super::OnCollected_Implementation();

	if (!HomingTarget) return; // HomingTarget is inherited from APRPickupBase

	// 1. CALCULATE XP AMOUNT (Based on the Picker's Stats)
	float FinalXPAward = Value;

	// --- XP GAIN LOGIC ---
	if (APRPlayerState* PS = HomingTarget->GetPlayerState<APRPlayerState>())
	{
		if (UPRStatsComponent* StatsComp = PS->StatsComponent)
		{
			const float XPGainModifier = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_XP_Gain);

			// Calculate based on picker's stats
			FinalXPAward = Value * XPGainModifier;

			UE_LOG(LogTemp, Log, TEXT("XP Shard Collected by %s. Base: %.1f, Mult: %.2fx, Final: %.1f"),*PS->GetPlayerName(), Value, XPGainModifier, FinalXPAward);
		}
	}
	// 2. OPTIONAL: SPLIT LOGIC (Disabled for now)
	// If enabled, divide XP by the number of players.
	
	//if (AGameStateBase* GS = GetWorld()->GetGameState())
	//{
	//	if (GS->PlayerArray.Num() > 0)
	//	{
	//		FinalXPAward /= GS->PlayerArray.Num();
	//	}
	//}
	// 
	// 3. DISTRIBUTE TO ALL PLAYERS
	if (APRGameState* GameState = GetWorld()->GetGameState<APRGameState>())
	{
		// Loop through all connected players via the GameState's PlayerArray.
		for (APlayerState* PS : GameState->PlayerArray)
		{
			if (APRPlayerState* RumblePS = Cast<APRPlayerState>(PS))
			{
				if (UPRStatsComponent* StatsComp = RumblePS->StatsComponent)
				{
					StatsComp->AddXP(FinalXPAward);
				}
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Shared XP Awarded: %.1f to %d players."), FinalXPAward, GameState->PlayerArray.Num());

	}
}


