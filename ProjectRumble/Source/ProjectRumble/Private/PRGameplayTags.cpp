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
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_Armor, "Stat.Primary.Armor");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_XP, "Stat.Primary.XP");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_MaxXP, "Stat.Primary.MaxXP");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Primary_Level, "Stat.Primary.Level");
		}
		namespace Offense
		{
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_Damage, "Stat.Offense.Damage");
			UE_DEFINE_GAMEPLAY_TAG(TAG_Stat_Offense_CritChance, "Stat.Offense.CritChance");
		}
	}
}