// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/PRGameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "PRGameplayTags.h"
#include "Kismet/GameplayStatics.h"

FDamageCalculationResult UPRGameplayStatics::CalculateFinalDamage(const UPRStatsComponent* AttackerStats, float BaseDamage, float BaseCritChance, float BaseCritMultiplier, const APRAIBase* Target)
{
	FDamageCalculationResult Result;
	if (!AttackerStats)
	{
		Result.FinalDamage = BaseDamage;
		return Result;
	}

	// --- 1. GET MODIFIERS FROM STATS COMPONENT ---
	const float AdditiveDamage = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Additive);
	const float MultiplicativeDamage = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Multiplicative);

	const float CritChanceBonus = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
	const float CritDamageBonus = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);

	// --- 2. CALCULATE INITIAL DAMAGE ---
	Result.FinalDamage = (BaseDamage + AdditiveDamage) * MultiplicativeDamage;

	// --- 3. CRIT CHANCE & CRIT DAMAGE LOGIC ---
	const float FinalCritChance = BaseCritChance + CritChanceBonus;
	if (FMath::FRand() < FinalCritChance)
	{
		Result.bWasCriticalHit = true;
		const float FinalCritMultiplier = BaseCritMultiplier + CritDamageBonus;
		Result.FinalDamage *= FinalCritMultiplier;
	}

	// --- 4. DAMAGE TO ELITES & BOSSES LOGIC ---
	if (Target && (Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Elite) || Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Boss)))
	{
		const float EliteDamageBonus = 1.0f + AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Elites);
		Result.FinalDamage *= EliteDamageBonus;
	}

	return Result;
}

float UPRGameplayStatics::ApplyRumbleDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass, const FVector& KnockbackDirection, float KnockbackMagnitude)
{
	// 1. Apply the standard damage
	const float ActualDamage = UGameplayStatics::ApplyDamage(DamagedActor, BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);

	// 2. If damage was applied and there's a knockback, apply it
	if (ActualDamage > 0.f && KnockbackMagnitude > 0.f)
	{
		if (ACharacter* TargetCharacter = Cast<ACharacter>(DamagedActor))
		{
			// Calculate the final launch velocity vector
			FVector LaunchVelocity = KnockbackDirection * KnockbackMagnitude;

			// Launch the character!
			TargetCharacter->LaunchCharacter(LaunchVelocity, true, true); // The bools override XY and Z velocity
		}
	}

	return ActualDamage;
}
