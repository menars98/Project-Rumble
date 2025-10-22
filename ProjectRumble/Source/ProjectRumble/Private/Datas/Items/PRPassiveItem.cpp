// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRPassiveItem.h"
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Datas/PRItemDefinition.h"
#include "Player/PRPlayerState.h"


void UPRPassiveItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects)
{
	Super::Initialize(InItemDefinition, InOwningActor, InitialEffects);
	// Store and apply the INITIAL effects
	AppliedEffects = InitialEffects;
	ApplyBonuses(AppliedEffects);
}

void UPRPassiveItem::LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects)
{
	Super::LevelUp(UpgradeEffects);

	AppliedEffects.Append(UpgradeEffects);
	ApplyBonuses(UpgradeEffects);
}

void UPRPassiveItem::ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply)
{
	if (!OwningActor || !ItemDefinition) return;

	APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor);
	if (!Player) return;

	UPRStatsComponent* StatsComp = Player->GetStatsComponent();
	if (!StatsComp) return;

	for (const FPotentialUpgradeEffect& Effect : EffectsToApply)
	{
		// The value to add is now in BaseMinMagnitude/BaseMaxMagnitude
		// because the RewardManager already "cooked" it for us.
		float ValueToAdd = Effect.BaseMinMagnitude;

		float CurrentValue = StatsComp->GetStatValue(Effect.TargetStat);

		StatsComp->SetStatValue(Effect.TargetStat, CurrentValue + ValueToAdd);
		UE_LOG(LogTemp, Warning, TEXT("TOME/ITEM APPLIED: Stat '%s' is now %f"), *Effect.TargetStat.ToString(), CurrentValue + ValueToAdd);
	}
}

void UPRPassiveItem::Uninitialize()
{
	// TODO: Implement logic to REMOVE the bonuses this tome granted.
	// This requires storing the applied bonuses or having a more advanced stat modification system.
}