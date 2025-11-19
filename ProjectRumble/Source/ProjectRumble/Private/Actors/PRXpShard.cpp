// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PRXpShard.h"
#include "Kismet/KismetMathLibrary.h" 
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"


APRXpShard::APRXpShard()
{
	PrimaryActorTick.bCanEverTick = true; 

	// Create basic components
	//DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	//RootComponent = DefaultSceneRoot;
	// TODO: Create StaticMesh and SphereCollision components here

}

void APRPickupBase::OnCollected_Implementation()
{
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
	// Call the parent's function first (good practice)
	Super::OnCollected_Implementation();

	if (!HomingTarget) return; // HomingTarget is inherited from APRPickupBase

	// --- XP GAIN LOGIC ---
	if (APRPlayerState* PS = HomingTarget->GetPlayerState<APRPlayerState>())
	{
		if (UPRStatsComponent* StatsComp = PS->StatsComponent)
		{
			const float XPGainModifier = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_XP_Gain);
			const float FinalXPAward = Value * (XPGainModifier); // "Value" is inherited

			UE_LOG(LogTemp, Log,TEXT("XP Shard Collected. Base Value: %.1f, Multiplier: %.2fx, Final XP: %.1f"),Value, XPGainModifier, FinalXPAward
			);

			StatsComp->AddXP(FinalXPAward);
		}
	}
}


