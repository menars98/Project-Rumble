#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

namespace NativeGameplayTags
{
	namespace Stats
	{
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_XP); //Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_MaxXP); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Level); //Flat
		}
		namespace Offense
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Additive); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Multiplicative); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_CritChance); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_CritDamage); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_AttackSpeed_Additive); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_AttackSpeed_Multiplicative); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileCount); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileSpeed); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Thorns); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_ProjectileBounce); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Size); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage_Elites); // Multiplicative vs Elites
		}
		namespace Defense
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Health); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_MaxHP); //Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Armor); //Flat, damage reduction
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_HealthRegen); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_LifeSteal); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Evasion); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_Shield); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_MaxShield); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_ShieldRegen); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_ShieldRegenDelay); // Flat
			//UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Defense_CooldownReduction); // Percentage
		}
		namespace Mobility
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_MovementSpeed_Base);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_MovementSpeed_Additive); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_MovementSpeed_Multiplicative); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_ExtraJump); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Mobility_JumpHeight); // Percentage
		}
		namespace Physics
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Physics_Knockback); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Physics_ThrowingForce); // Percentage
		}
		namespace Utility
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_XP_Gain); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Gold_Gain); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Silver_Gain); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Duration); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Luck); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_Difficulty); // Percentage
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PickRange); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PowerupMultiplier); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_PowerDropChance); // Multiplicative
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Utiliy_EliteSpawnChance); // Multiplicative
		}
		namespace Resource
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Resource_Gold); // Flat
			//UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Resource_Silver); // Flat
		}
		namespace AI
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_BaseKnockback); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_ContactDamage) // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_XP_Reward); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_Gold_Reward); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_Silver_Reward); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_AttackRange); // Flat
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_AI_AttackDamage)
		}
	}

	namespace EnemyTypes
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemy_Type_Normal);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemy_Type_Elite);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemy_Type_Boss);
	}

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_IsStunned);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_IsDead);
	}
	namespace StatusEffect
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Effect_StunChance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Effect_StunDuration);
	}
	namespace Enemies
	{
		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Type_Goblin);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Type_Skeleton);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Type_Neuron);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Type_Cactus);
		}
	}
	namespace Destructible
	{
		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Destructible_Type_Vase);
		}
	}
}
