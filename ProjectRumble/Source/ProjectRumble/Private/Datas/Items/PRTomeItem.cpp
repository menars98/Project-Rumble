// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRTomeItem.h"
#include "Characters/PRCharacterBase.h"
#include "Components/PRStatsComponent.h"
#include "Datas/PRItemDefinition.h"
#include "Player/PRPlayerState.h"


void UPRTomeItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor)
{
	Super::Initialize(InItemDefinition, InOwningActor);
	ApplyBonuses();
}

void UPRTomeItem::LevelUp()
{
	Super::LevelUp();

	// Note: A simple "re-apply" might not work if bonuses stack.
	// A more robust system would remove old bonuses before applying new ones.
	// For now, this is a simplification.
	ApplyBonuses();
}

void UPRTomeItem::ApplyBonuses()
{
	if (!OwningActor || !ItemDefinition) return;

	APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor);
	if (!Player) return;

	UPRStatsComponent* StatsComp = Player->GetStatsComponent();
	if (!StatsComp) return;

	// This is a simple implementation. A real system would get the effects for the CURRENT level.
	// For now, let's assume the effects in the ItemDefinition are what we apply.
	for (const FPotentialUpgradeEffect& Effect : ItemDefinition->PotentialUpgradeEffects)
	{
		// For a Tome, we can just take the average of the min/max magnitude as the bonus.
		float ValueToAdd = (Effect.BaseMinMagnitude + Effect.BaseMaxMagnitude) / 2.0f;

		// Get the correct stat tag to modify based on the effect's target.
		// Example: TargetStat is "Stat.Offense.Damage", we need to modify "Stat.Offense.Damage.Multiplicative"
		// THIS LOGIC IS COMPLEX. LET'S SIMPLIFY FOR THE PROTOTYPE.

		// --- SIMPLIFIED PROTOTYPE LOGIC ---
		// Let's assume the Tome's "PotentialUpgradeEffects" already has the CORRECT target stat
		// (e.g., Stat.Offense.Damage.Multiplicative).

		float CurrentValue = StatsComp->GetStatValue(Effect.TargetStat);

		// We are simply adding the bonus. Since our TargetStat is already specific
		// (e.g., Additive or Multiplicative), we don't need to check the operation.
		float NewValue = CurrentValue + ValueToAdd;

		StatsComp->SetStatValue(Effect.TargetStat, NewValue);

		UE_LOG(LogTemp, Log, TEXT("Tome '%s' applied bonus to stat %s. New value: %f"), *ItemDefinition->DisplayName.ToString(), *Effect.TargetStat.ToString(), NewValue);
	}
}

void UPRTomeItem::Uninitialize()
{
	// TODO: Implement logic to REMOVE the bonuses this tome granted.
	// This requires storing the applied bonuses or having a more advanced stat modification system.
}