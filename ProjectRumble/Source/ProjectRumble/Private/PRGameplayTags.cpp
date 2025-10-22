#include "PRGameplayTags.h"
#include "GameplayTagsManager.h"

namespace NativeGameplayTags
{
	namespace Stats
	{
		namespace Primary
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_Health, "Stat.Primary.Health");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_MaxHP, "Stat.Primary.MaxHP");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_XP, "Stat.Primary.XP");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_MaxXP, "Stat.Primary.MaxXP");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_Level, "Stat.Primary.Level");
		}
		namespace Offense
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Damage_Additive, "Stat.Offense.Damage.Additive");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Damage_Multiplicative, "Stat.Offense.Damage.Multiplicative");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_AttackSpeed_Additive, "Stat.Offense.AttackSpeed.Additive");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_AttackSpeed_Multiplicative, "Stat.Offense.AttackSpeed.Multiplicative");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_ProjectileCount, "Stat.Offense.ProjectileCount");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_ProjectileSpeed, "Stat.Offense.ProjectileSpeed");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_CritChance, "Stat.Offense.CritChance");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_CritDamage, "Stat.Offense.CritDamage");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Thorns, "Stat.Offense.Thorns");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_ProjectileBounce, "Stat.Offense.ProjectileBounce");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Size, "Stat.Offense.Size");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Damage_Elites, "Stat.Offense.Damage.Elites");
			
		}
		namespace Defense
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_Armor, "Stat.Defense.Armor");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_HealthRegen, "Stat.Defense.HealthRegen");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_LifeSteal, "Stat.Defense.LifeSteal");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_Evasion, "Stat.Defense.Evasion");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_Shield, "Stat.Defense.Shield");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_MaxShield, "Stat.Defense.MaxShield");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_ShieldRegen, "Stat.Defense.ShieldRegen");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Defense_ShieldRegenDelay, "Stat.Defense.ShieldRegenDelay");
		}
		namespace Mobility
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Mobility_MovementSpeed_Additive, "Stat.Mobility.MovementSpeed.Additive");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Mobility_MovementSpeed_Multiplicative, "Stat.Mobility.MovementSpeed.Multiplicative");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Mobility_ExtraJump, "Stat.Mobility.ExtraJump");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Mobility_JumpHeight, "Stat.Mobility.JumpHeight");
		}
		namespace Physics
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Physics_Knockback, "Stat.Physics.Knockback");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Physics_ThrowingForce, "Stat.Physics.ThrowingForce");
		}
		namespace Utility
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_XP_Gain, "Stat.Utility.XP_Gain");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_Gold_Gain, "Stat.Utility.Gold_Gain");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_Silver_Gain, "Stat.Utility.Silver_Gain");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_Duration, "Stat.Utility.Duration");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_Luck, "Stat.Utility.Luck");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_Difficulty, "Stat.Utility.Difficulty");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_PickRange, "Stat.Utility.PickRange");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_PowerupMultiplier, "Stat.Utility.PowerUpMultiplier");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_PowerDropChance, "Stat.Utility.PowerDropChance");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Utiliy_EliteSpawnChance, "Stat.Utility.EliteSpawnChance");
		}
	}

	namespace EnemyTypes
	{
		UE_DEFINE_GAMEPLAY_TAG(TAG_Enemy_Type_Normal, "Enemy.Type.Normal");
		UE_DEFINE_GAMEPLAY_TAG(TAG_Enemy_Type_Elite, "Enemy.Type.Elite");
		UE_DEFINE_GAMEPLAY_TAG(TAG_Enemy_Type_Boss, "Enemy.Type.Boss");
	}

	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG(TAG_State_IsStunned, "State.IsStunned");
		UE_DEFINE_GAMEPLAY_TAG(TAG_State_IsDead, "State.IsDead");
	}

	namespace StatusEffect
	{
		UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Effect_StunChance, "Stat.Effect.StunChance");
		UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Effect_StunDuration, "Stat.Effect.StunDuration");
	}
}