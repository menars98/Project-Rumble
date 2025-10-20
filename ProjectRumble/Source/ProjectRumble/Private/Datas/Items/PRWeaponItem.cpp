// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRWeaponItem.h"
#include "Characters/PRCharacterBase.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "Datas/PRItemDefinition.h"
#include "PRGameplayTags.h"
#include "TimerManager.h" 

void UPRWeaponItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FUpgradeEffect>& InitialEffects)
{
	Super::Initialize(InItemDefinition, InOwningActor, InitialEffects);

	UE_LOG(LogTemp, Error, TEXT("WEAPON INITIALIZE CALLED for %s!"), *InItemDefinition->DisplayName.ToString());
	// --- START THE ATTACK LOOP ---
	// Check if we have a valid world to set a timer in.
	if (UWorld* World = GetWorld())
	{
		// Set a timer to call our Attack() function after an initial delay (optional, 0 for immediate)
		// and then loop forever.
		// For the first attack, we can call it directly.
		Attack();
	}
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
	// Get the actual class name of this object instance and print it.
	FString ClassName = GetClass()->GetName();
	UE_LOG(LogTemp, Error, TEXT("ATTACKING WITH CLASS: %s"), *ClassName);

	if (!OwningActor) return;

	// Perform the attack logic defined in the Blueprint.
	ExecuteAttack();

	// Set the timer to call this function again after the cooldown.
	const float Cooldown = GetCalculatedCooldown();
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UPRWeaponItem::Attack, Cooldown, false);
}

float UPRWeaponItem::GetCalculatedCooldown() const
{
	float WeaponBaseCooldown = ItemDefinition->WeaponStats.BaseCooldown;

	float AdditiveBonus = 0.0f;
	float MultiplicativeBonus = 0.0f;

	float FinalCooldown = 0.0f;
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			AdditiveBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Additive);
			MultiplicativeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Multiplicative);

			// Ensure the multiplier is not zero or negative to prevent division by zero
			if (MultiplicativeBonus <= 0.f)
			{
				MultiplicativeBonus = 1.0f;
			}

			// FORMULA: (Base - Additive) / Multiplicative
			// Attack speed increases, cooldown decreases. So we use division.
			FinalCooldown = (WeaponBaseCooldown - AdditiveBonus) / MultiplicativeBonus;
		}
	}

	return FMath::Max(FinalCooldown, 0.1f); // Ensure cooldown doesn't become zero or negative
}

float UPRWeaponItem::GetCalculatedDamage() const
{
	if (!ItemDefinition) return 0.f;

	// 1. Get the weapon's own base damage
	float WeaponBaseDamage = ItemDefinition->WeaponStats.BaseDamage;

	// TODO: Add damage scaling from the weapon's own level. This could also be an additive bonus.

	float AdditiveBonus = 0.f;
	float MultiplicativeBonus = 1.0f; // Start at 1.0 for multiplication

	// 2. Get all modifiers from the player's StatsComponent
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			AdditiveBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Additive);

			// Multiplicative bonuses are added together (e.g., 0.1 + 0.05 = 0.15 for +15%)
			MultiplicativeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Multiplicative);
		}
	}

	// 3. Calculate the final damage
	// FORMULA: (Base + Additive) * Multiplicative
	const float FinalDamage = (WeaponBaseDamage + AdditiveBonus) * MultiplicativeBonus;

	return FinalDamage;
}

float UPRWeaponItem::GetCalculatedCritChance() const
{
	if (!ItemDefinition) return 0.f;

	float WeaponBaseCritChance = 0.0f;

	float AdditiveBonus = 0.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			WeaponBaseCritChance = ItemDefinition->WeaponStats.BaseCritChance; 

			AdditiveBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
		}
	}
	
	// FORMULA: Base + Additive, @TODO: Maybe we dont have to clamp? We can take surplus chance and increase crit damage?
	return FMath::Clamp(WeaponBaseCritChance + AdditiveBonus, 0.f, 1.f); // Clamp to 0-1 range (0% to 100%)
}

float UPRWeaponItem::GetCalculatedCritDamage() const
{
	if (!ItemDefinition) return 1.5f; // Return a safe default if no definition

	// 1. Get the base critical damage multiplier from the weapon's definition.
	float BaseMultiplier = ItemDefinition->WeaponStats.BaseCritDamageMultiplier;

	// 2. Get the additional critical damage bonus from the player's global stats.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// The CritDamage stat is an additive bonus on top of the base multiplier.
			// e.g., Base 2 + 0.5 from items = 2.5x total multiplier.
			const float BonusMultiplier = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);
			return BaseMultiplier + BonusMultiplier;
		}
	}

	// If we can't find stats, return the weapon's base multiplier.
	return BaseMultiplier;
}

float UPRWeaponItem::GetCalculatedSize() const
{
	if (!ItemDefinition || !OwningActor) return 1.0f;

	float BaseSize = ItemDefinition->WeaponStats.BaseSize;
	float MultiplicativeBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Size.Multiplicative"
			MultiplicativeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Size);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseSize * MultiplicativeBonus;
}

float UPRWeaponItem::GetCalculatedKnockback() const
{
	if (!ItemDefinition || !OwningActor) return 0.f;

	float BaseKnockback = ItemDefinition->WeaponStats.BaseKnockback;
	float MultiplicativeBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Knockback.Multiplicative"
			MultiplicativeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Physics::TAG_Stat_Physics_Knockback);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseKnockback * MultiplicativeBonus;
}

float UPRWeaponItem::GetCalculatedDuration() const
{
	if (!ItemDefinition || !OwningActor) return 0.f;

	float BaseDuration = ItemDefinition->WeaponStats.BaseDuration;
	float MultiplicativeBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Duration.Multiplicative"
			MultiplicativeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Duration);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseDuration * MultiplicativeBonus;
}

// @TODO Change it to float because we keep count number float but cast to int32 when spawning projectiles
int32 UPRWeaponItem::GetCalculatedProjectileBounce() const
{
	if (!ItemDefinition || !OwningActor) return 0;

	int32 BaseBounces = ItemDefinition->WeaponStats.BaseProjectileBounce;
	int32 BonusBounces = 0;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.ProjectileBounce"
			BonusBounces = static_cast<int32>(StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileBounce));
		}
	}

	// FORMULA: Base + Additive
	return BaseBounces + BonusBounces;
}

// @TODO Change it to float because we keep count number float but cast to int32 when spawning projectiles
int32 UPRWeaponItem::GetCalculatedProjectileCount() const
{
	if (!ItemDefinition || !OwningActor) return 1;

	// 1. Get the base count from the weapon's definition
	int32 BaseCount = ItemDefinition->WeaponStats.BaseProjectileCount;

	// @TODO: Maybe Add scaling per level from the item itself (e.g., at level 5, BaseCount becomes 2)

	// 2. Get the additive bonus from the player's global stats
	int32 BonusCount = 0;
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			FGameplayTag ProjectileCountTag = NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileCount;
			BonusCount = static_cast<int32>(StatsComp->GetStatValue(ProjectileCountTag));
		}
	}

	// Final count is the base + bonus
	return BaseCount + BonusCount;
}

float UPRWeaponItem::GetCalculatedProjectileSpeed() const
{
	if (!ItemDefinition) return 0.f;

	// 1. Get the base projectile speed from the weapon's definition
	float BaseSpeed = ItemDefinition->WeaponStats.BaseProjectileSpeed;

	float ProjectileSpeedModifier = 1.0f;

	// 2. Get the multiplicative speed bonus from the player's global stats
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			 ProjectileSpeedModifier = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileSpeed);
		}
	}

	return BaseSpeed * ProjectileSpeedModifier;
}

FDamageCalculationResult UPRWeaponItem::CalculateFinalDamage(const APRAIBase* Target)
{
	FDamageCalculationResult Result;
	if (!OwningActor || !Target) return Result;

	// Start with the weapon's calculated base damage
	Result.FinalDamage = GetCalculatedDamage();

	// --- CRIT CHANCE & CRIT DAMAGE LOGIC ---
	const float CritChance = GetCalculatedCritChance();
	if (FMath::FRand() < CritChance)
	{
		Result.bWasCriticalHit = true;
		const float CritDamageMultiplier = GetCalculatedCritDamage(); // Needs a new GetCalculated... function
		Result.FinalDamage *= CritDamageMultiplier;
	}

	// --- DAMAGE TO ELITES & BOSSES LOGIC ---
	if (Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Elite) || Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Boss))
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
			if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
			{
				const float EliteDamageBonus = 1.0f + StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Elites);
				Result.FinalDamage *= EliteDamageBonus;
			}
		}
	}

	return Result;
}
