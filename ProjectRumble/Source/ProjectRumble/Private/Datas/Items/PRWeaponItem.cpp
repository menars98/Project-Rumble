// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRWeaponItem.h"
#include "Characters/PRCharacterBase.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "Datas/PRItemDefinition.h"
#include "PRGameplayTags.h"
#include "TimerManager.h" 

void UPRWeaponItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects)
{
	Super::Initialize(InItemDefinition, InOwningActor, InitialEffects);

	UE_LOG(LogTemp, Error, TEXT("WEAPON INITIALIZE CALLED for %s!"), *InItemDefinition->DisplayName.ToString());

	// Store and apply the initial effects for this weapon
	AppliedEffects = InitialEffects;
	ApplyBonuses(AppliedEffects);

	// Start the attack loop
	if (GetWorld())
	{
		Attack();
	}
}

void UPRWeaponItem::LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects)
{
	Super::LevelUp(UpgradeEffects);

	// Add the new upgrade effects to our total list
	AppliedEffects.Append(UpgradeEffects);

	// Apply ONLY the new bonuses from this level up
	ApplyBonuses(UpgradeEffects);

	// When the weapon levels up, its stats (like cooldown) might change.
	// We need to restart the timer with the new calculated cooldown.
	if (OwningActor && GetWorld())
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

	float AdditiveBonusPercent = 0.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			WeaponBaseCritChance = ItemDefinition->WeaponStats.BaseCritChance;

			AdditiveBonusPercent = WeaponBaseCritChance + StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
		}
	}
	
	float FinalCritChance = (WeaponBaseCritChance + AdditiveBonusPercent);

	// FORMULA: Base + Additive, @TODO: Maybe we dont have to clamp? We can take surplus chance and increase crit damage?
	return FMath::Clamp(FinalCritChance, 0.f, 1.f); // Clamp to 0-1 range (0% to 100%)
}

float UPRWeaponItem::GetCalculatedCritDamage() const
{
	if (!ItemDefinition) return 2.0f; // Return a safe default if no definition

	// Base critical damage multiplier is always 2.0x (200%)
	float BaseMultiplier = 2.0f;

	// 2. Get the additional critical damage bonus from the player's global stats.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// The CritDamage stat is an additive bonus on top of the base multiplier.
			// e.g., Base 2 + 0.5 from items = 2.5x total multiplier.
			const float BonusMultiplier = BaseMultiplier + StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);
			return BonusMultiplier;
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

float UPRWeaponItem::GetCalculatedStunChance() const
{
	if (!ItemDefinition) return 0.0f;

	// 1. Get the weapon's base stun chance (e.g., a heavy mace might have a high base chance).
	// This value should be in the 0-1 range.
	float BaseChance = ItemDefinition->WeaponStats.BaseStunChance;

	// 2. Get the additive bonus from the player's global stats.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Player's bonus is also additive (e.g., 0.1 for +10% chance).
			const float BonusChance = StatsComp->GetStatValue(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunChance);
			BaseChance += BonusChance;
		}
	}

	// Clamp the final chance between 0% and 100%.
	return FMath::Clamp(BaseChance, 0.f, 1.f);
}

float UPRWeaponItem::GetCalculatedStunDuration() const
{
	if (!ItemDefinition) return 0.0f;

	// 1. Get the weapon's base stun duration.
	float BaseDuration = ItemDefinition->WeaponStats.BaseStunDuration;

	// 2. Get the multiplicative bonus from the player's global stats.
	// Duration is often multiplicative.
	float Multiplier = 1.0f;
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming you have a "Stat.Effect.StunDuration.Multiplicative" tag.
			// Let's use a single tag for simplicity for now.
			const float BonusMultiplier = StatsComp->GetStatValue(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunDuration);
			Multiplier += BonusMultiplier; // e.g., 1.0 + 0.2 = 1.2x duration
		}
	}

	return BaseDuration * Multiplier;
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

void UPRWeaponItem::ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply)
{
	if (!OwningActor) return;

	APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor);
	if (!Player) return;

	UPRStatsComponent* StatsComp = Player->GetStatsComponent();
	if (!StatsComp) return;

	// Loop through the FINAL, ROLLED effects passed into this function.
	for (const FPotentialUpgradeEffect& Effect : EffectsToApply)
	{
		// The magnitude is already rolled, so we use it directly.
		float ValueToAdd = Effect.BaseMinMagnitude;

		float CurrentValue = StatsComp->GetStatValue(Effect.TargetStat);

		StatsComp->SetStatValue(Effect.TargetStat, CurrentValue + ValueToAdd);
		UE_LOG(LogTemp, Warning, TEXT("WEAPON APPLIED: Stat '%s' is now %f"), *Effect.TargetStat.ToString(), CurrentValue + ValueToAdd);
	}
}