#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

namespace NativeGameplayTags
{
	namespace Stats
	{
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Health); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_MaxHP); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_XP); //Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_MaxXP); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Level); //Flat
		}
		namespace Offense
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Additive); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Multiplicative); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_CritChance); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_AttackSpeed_Additive); // For flat cooldown reduction
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_AttackSpeed_Multiplicative); // For percentage increases
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileCount); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileSpeed); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Thorns); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileBounce); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Size); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Elites); // Percentage vs Elites
		}
		namespace Defense
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Armor); //Flat, damage reduction
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_HealthRegen); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_ShieldStrength); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_LifeSteal); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Evasion); // Percentage
			//UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_ShieldRegen); // Flat
			//UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_CooldownReduction); // Percentage
		}
		namespace Mobility
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_MovementSpeed_Additive); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_MovementSpeed_Multiplicative); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_ExtraJump); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_JumpHeight); // Percentage
		}
		namespace Physics
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Physics_Knockback); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Physics_ThrowingForce); // Percentage
		}
		namespace Utility
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_XP_Gain); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Gold_Gain); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Silver_Gain); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Duration); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Luck); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Difficulty); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PickRange); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PowerupMultiplier); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PowerDropChance); // Percentage
		}
	}
}
