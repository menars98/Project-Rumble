// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRWeaponItem.h"
#include "Characters/PRCharacterBase.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "PRGameplayTags.h"
#include "TimerManager.h" 

void UPRWeaponItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor)
{
	Super::Initialize(InItemDefinition, InOwningActor);

	// Start the attack loop when the weapon is first acquired.
	Attack();
}

void UPRWeaponItem::LevelUp()
{
	Super::LevelUp();

	// When the weapon levels up, its stats (like cooldown) might change.
	// We need to restart the timer with the new calculated cooldown.
	if (OwningActor)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		Attack(); // Restart the loop immediately
	}
}

void UPRWeaponItem::Attack()
{
	if (!OwningActor) return;

	// Perform the attack logic defined in the Blueprint.
	ExecuteAttack();

	// Set the timer to call this function again after the cooldown.
	const float Cooldown = GetCalculatedCooldown();
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UPRWeaponItem::Attack, Cooldown, false);
}

float UPRWeaponItem::GetCalculatedCooldown() const
{
	// This is a placeholder. A real implementation would get base cooldown from the ItemDefinition
	// and the AttackSpeed modifier from the player's StatsComponent.
	float BaseCooldown = 2.0f; // TODO: Get from ItemDefinition

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming AttackSpeed modifier is multiplicative (e.g., 0.1 for +10% speed).
			// Cooldown = BaseCooldown / (1 + AttackSpeedModifier)
			const float AttackSpeedMod = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed);
			if (1.0f + AttackSpeedMod > 0)
			{
				return BaseCooldown / (1.0f + AttackSpeedMod);
			}
		}
	}

	return BaseCooldown;
}