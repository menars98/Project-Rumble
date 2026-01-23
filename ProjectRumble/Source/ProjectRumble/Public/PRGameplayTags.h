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
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_PierceCount); // Flat 
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
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Type_VoidWalker);
		}
		namespace Tier
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Tier_1); // Fodder (Goblin, Skeleton)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Tier_2); // Medium (Cactus)
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Tier_3); // Elite
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Tier_Endless);
		}
		namespace Biome
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Biome_Forest);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Biome_Desert);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Enemies_Biome_Global); // Appears everywhere
		}
	}

	namespace Destructible
	{
		namespace Type
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Destructible_Type_Vase);
		}
	}

	namespace Tracker
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Main_Combat_Kills);				// Total Kill
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Main_Combat_DamageDealt);			// Total Damage
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Main_Combat_DamageTaken);			// Total Damage Taken
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Main_Combat_DiedTo);				// Died To
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Survival_Health_Healing_Regen);     // Regen
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Survival_Time_TimeAlive);			// Alive Time(sec)
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Survival_Health_Healing_Lifesteal);	// Lifesteal
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Main_Economy_GoldEarned);			// Gold Earned
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Tracker_Combat_Damage_DamageDealt);
		
	}

	namespace UI_Layers
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_Layer_Game);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_Layer_Menu);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UI_Layer_Modal);
	}

	namespace ItemTypes
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Type_Weapon); // "Item.Weapon"
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Item_Type_Passive); // "Item.Passive"
	}

	namespace Status
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Status_Poison_PoisonCap); // Default 5
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Status_Poison_PoisonStacks);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Status_Imbue_Poison);
	}
}
