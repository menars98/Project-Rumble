// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PRGoldPickup.h"
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"

void APRGoldPickup::BeginPlay()
{
	Super::BeginPlay();

}

void APRGoldPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APRGoldPickup::OnCollected_Implementation()
{
	// Security Check
	if (!HasAuthority())
	{
		return;
	}

	Super::OnCollected_Implementation();

	if (!HomingTarget) return;

	// --- GOLD GRANT LOGIC ---
	if (APRPlayerState* PS = HomingTarget->GetPlayerState<APRPlayerState>())
	{
		if (UPRStatsComponent* StatsComp = PS->StatsComponent)
		{
			// Get player's current GoldGain modifier
			const float GoldGainModifier = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Gold_Gain);

			// Calculate the final Gold to grant
			const float FinalGoldAward = Value * (GoldGainModifier);
			const int32 RoundedGold = FMath::RoundToInt(FinalGoldAward);

			if (RoundedGold > 0)
			{
				const float CurrentGold = StatsComp->GetStatValue(NativeGameplayTags::Stats::Resource::TAG_Stat_Resource_Gold);
				StatsComp->SetStatValue(NativeGameplayTags::Stats::Resource::TAG_Stat_Resource_Gold, CurrentGold + RoundedGold);
			}
		}
	}
}


