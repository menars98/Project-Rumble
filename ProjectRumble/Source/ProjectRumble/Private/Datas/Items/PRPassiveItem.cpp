// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRPassiveItem.h"
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Datas/PRItemDefinition.h"
#include "Datas/PRPassiveItemDefinition.h"
#include "Player/PRPlayerState.h"


void UPRPassiveItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects)
{
	Super::Initialize(InItemDefinition, InOwningActor, InitialEffects);
	// Store and apply the INITIAL effects
	AppliedEffects = InitialEffects;
	RecalculateAndApplyStats();

	PassiveDefinition = Cast<UPRPassiveItemDefinition>(InItemDefinition);

	// --- AUTO-BIND ---
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(InOwningActor))
	{
		if (UPRStatsComponent* Stats = Player->GetStatsComponent())
		{
			// Save the last known XP
			LastKnownXP = Stats->GetStatValue(NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_XP);

			// Subscribe to XP 
			Stats->OnXPChangedDelegate.AddDynamic(this, &UPRPassiveItem::HandleXPChanged);

			UE_LOG(LogTemp, Warning, TEXT("ITEM: %s successfully bound to XP Delegate."), *GetName());
		}
	}

	ReceiveInitialize();
	
	if (PassiveDefinition && PassiveDefinition->AbilityStats.Cooldown > 0.0f)
	{
		StartAbilityTimer(PassiveDefinition->AbilityStats.Cooldown);
	}
}

void UPRPassiveItem::Deactivate()
{
	// Clean up when we die or when items are deleted
	if (!OwningActor) return;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// We are taking back all the bonuses we gave out.
			for (const TPair<FGameplayTag, float>& Pair : GrantedBonusesMap)
			{
				float CurrentVal = StatsComp->GetStatValue(Pair.Key);
				StatsComp->SetStatValue(Pair.Key, CurrentVal - Pair.Value);
			}
		}
	}

	// Clear the memory
	GrantedBonusesMap.Empty();

	// --- UNBIND ---
	if (OwningActor)
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
			if (UPRStatsComponent* Stats = Player->GetStatsComponent())
			{
				Stats->OnXPChangedDelegate.RemoveDynamic(this, &UPRPassiveItem::HandleXPChanged);
			}
		}
	}

	Super::Deactivate();
}

void UPRPassiveItem::LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects)
{
	Super::LevelUp(UpgradeEffects);

	AppliedEffects.Append(UpgradeEffects);
	RecalculateAndApplyStats();
}

void UPRPassiveItem::RecalculateAndApplyStats()
{
	if (!OwningActor) return;

	APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor);
	if (!Player) return;

	UPRStatsComponent* StatsComp = Player->GetStatsComponent();
	if (!StatsComp) return;

	// --- STEP 1: DELETE OLD BONUSES ---
	// If this item previously provided stats, let's retrieve them first.
	// This way, we avoid the “Level 1 bonus + Level 2 bonus” error.
	for (const TPair<FGameplayTag, float>& Pair : GrantedBonusesMap)
	{
		float CurrentVal = StatsComp->GetStatValue(Pair.Key);
		StatsComp->SetStatValue(Pair.Key, CurrentVal - Pair.Value);
	}

	
	//Clear the map; 
	GrantedBonusesMap.Empty();


	// --- STEP 2: CALCULATE NEW TOTALS ---
	// Add up ALL cards in the AppliedEffects array.
	// (Add the +10 from Level 1, the +5 from Level 2... Add them all up).
	for (const FPotentialUpgradeEffect& Effect : AppliedEffects)
	{
		// Note: We assume that “Rolled Value” (the rolled value) is stored in BaseMinMagnitude.
		// RewardManager was setting this.
		float& TotalBonus = GrantedBonusesMap.FindOrAdd(Effect.TargetStat);
		TotalBonus += Effect.BaseMinMagnitude;
	}


	// --- STEP 3: APPLY NEW BONUSES ---
	for (const TPair<FGameplayTag, float>& Pair : GrantedBonusesMap)
	{
		FGameplayTag StatTag = Pair.Key;
		float NewBonusAmount = Pair.Value;

		float CurrentVal = StatsComp->GetStatValue(StatTag);
		StatsComp->SetStatValue(StatTag, CurrentVal + NewBonusAmount);

		UE_LOG(LogTemp, Log, TEXT("Passive Update: %s grants TOTAL %.1f to %s"), *GetName(), NewBonusAmount, *StatTag.ToString());
	}
}

void UPRPassiveItem::StartAbilityTimer(float Cooldown)
{
	if (UWorld* World = GetWorld())
	{
		// ExecutePassiveAbility fonksiyonunu (BP Eventi) sürekli çaðýr
		World->GetTimerManager().SetTimer(AbilityTimerHandle, this, &UPRPassiveItem::TriggerAbility, Cooldown, true);
	}
}

void UPRPassiveItem::TriggerAbility()
{
	ExecutePassiveAbility();
}

void UPRPassiveItem::HandleXPChanged(float CurrentXP, float MaxXP)
{
	float AmountGained = CurrentXP - LastKnownXP;

	UE_LOG(LogTemp, Warning, TEXT("ITEM: HandleXPChanged C++ Triggered! Gained: %f"), AmountGained);

	// If the level has been increased, XP may have been reset (resulting in a negative value), so it needs to be corrected.
	// Let's keep it simple for now; we'll address the level increase separately.
	if (AmountGained < 0) AmountGained = CurrentXP; // Tahmini fix

	LastKnownXP = CurrentXP;

	// Only notify Blueprint if the amount is positive
	if (AmountGained > 0.0f)
	{
		OnXPGained(AmountGained, CurrentXP);
	}
}

void UPRPassiveItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Send the series to the client
	DOREPLIFETIME(UPRPassiveItem, AppliedEffects);
}
