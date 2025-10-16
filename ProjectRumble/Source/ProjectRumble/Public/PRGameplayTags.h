#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

namespace NativeGameplayTags
{
	namespace Stats
	{
		namespace Primary
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Health);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_MaxHP);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Armor);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_XP);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_MaxXP);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Primary_Level);
		}
		namespace Offense
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_Damage);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_CritChance);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Stat_Offense_AttackSpeed);
		}
	}
}
