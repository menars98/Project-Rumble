// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PRTypes.h"
#include "GameplayTagContainer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRTypes() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EFaction();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EModifierOperation();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EUpgradeType();
PROJECTRUMBLE_API UScriptStruct* Z_Construct_UScriptStruct_FStatDefinition();
PROJECTRUMBLE_API UScriptStruct* Z_Construct_UScriptStruct_FUpgradeEffect();
PROJECTRUMBLE_API UScriptStruct* Z_Construct_UScriptStruct_FUpgradePoolEntry();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EFaction ******************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EFaction;
static UEnum* EFaction_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EFaction.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EFaction.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProjectRumble_EFaction, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("EFaction"));
	}
	return Z_Registration_Info_UEnum_EFaction.OuterSingleton;
}
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EFaction>()
{
	return EFaction_StaticEnum();
}
struct Z_Construct_UEnum_ProjectRumble_EFaction_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Enemy.Name", "EFaction::Enemy" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
		{ "Neutral.Name", "EFaction::Neutral" },
		{ "Player.Name", "EFaction::Player" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EFaction::Player", (int64)EFaction::Player },
		{ "EFaction::Enemy", (int64)EFaction::Enemy },
		{ "EFaction::Neutral", (int64)EFaction::Neutral },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProjectRumble_EFaction_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble,
	nullptr,
	"EFaction",
	"EFaction",
	Z_Construct_UEnum_ProjectRumble_EFaction_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EFaction_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EFaction_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProjectRumble_EFaction_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProjectRumble_EFaction()
{
	if (!Z_Registration_Info_UEnum_EFaction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EFaction.InnerSingleton, Z_Construct_UEnum_ProjectRumble_EFaction_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EFaction.InnerSingleton;
}
// ********** End Enum EFaction ********************************************************************

// ********** Begin Enum EModifierOperation ********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EModifierOperation;
static UEnum* EModifierOperation_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EModifierOperation.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EModifierOperation.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProjectRumble_EModifierOperation, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("EModifierOperation"));
	}
	return Z_Registration_Info_UEnum_EModifierOperation.OuterSingleton;
}
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EModifierOperation>()
{
	return EModifierOperation_StaticEnum();
}
struct Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Additive.Name", "EModifierOperation::Additive" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
		{ "Multiplicative.Comment", "// Adds to the base value (e.g., +10 HP, +1 Projectile)\n" },
		{ "Multiplicative.Name", "EModifierOperation::Multiplicative" },
		{ "Multiplicative.ToolTip", "Adds to the base value (e.g., +10 HP, +1 Projectile)" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EModifierOperation::Additive", (int64)EModifierOperation::Additive },
		{ "EModifierOperation::Multiplicative", (int64)EModifierOperation::Multiplicative },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble,
	nullptr,
	"EModifierOperation",
	"EModifierOperation",
	Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProjectRumble_EModifierOperation()
{
	if (!Z_Registration_Info_UEnum_EModifierOperation.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EModifierOperation.InnerSingleton, Z_Construct_UEnum_ProjectRumble_EModifierOperation_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EModifierOperation.InnerSingleton;
}
// ********** End Enum EModifierOperation **********************************************************

// ********** Begin Enum EUpgradeType **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EUpgradeType;
static UEnum* EUpgradeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EUpgradeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EUpgradeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProjectRumble_EUpgradeType, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("EUpgradeType"));
	}
	return Z_Registration_Info_UEnum_EUpgradeType.OuterSingleton;
}
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EUpgradeType>()
{
	return EUpgradeType_StaticEnum();
}
struct Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
		{ "NewPassiveItem.Name", "EUpgradeType::NewPassiveItem" },
		{ "NewWeapon.Name", "EUpgradeType::NewWeapon" },
		{ "StatBonus.Name", "EUpgradeType::StatBonus" },
		{ "UpgradePassiveItem.Comment", "// Tomes, Relics etc.\n" },
		{ "UpgradePassiveItem.Name", "EUpgradeType::UpgradePassiveItem" },
		{ "UpgradePassiveItem.ToolTip", "Tomes, Relics etc." },
		{ "UpgradeWeapon.Name", "EUpgradeType::UpgradeWeapon" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EUpgradeType::NewWeapon", (int64)EUpgradeType::NewWeapon },
		{ "EUpgradeType::UpgradeWeapon", (int64)EUpgradeType::UpgradeWeapon },
		{ "EUpgradeType::NewPassiveItem", (int64)EUpgradeType::NewPassiveItem },
		{ "EUpgradeType::UpgradePassiveItem", (int64)EUpgradeType::UpgradePassiveItem },
		{ "EUpgradeType::StatBonus", (int64)EUpgradeType::StatBonus },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble,
	nullptr,
	"EUpgradeType",
	"EUpgradeType",
	Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProjectRumble_EUpgradeType()
{
	if (!Z_Registration_Info_UEnum_EUpgradeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EUpgradeType.InnerSingleton, Z_Construct_UEnum_ProjectRumble_EUpgradeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EUpgradeType.InnerSingleton;
}
// ********** End Enum EUpgradeType ****************************************************************

// ********** Begin ScriptStruct FStatDefinition ***************************************************
static_assert(std::is_polymorphic<FStatDefinition>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FStatDefinition cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStatDefinition;
class UScriptStruct* FStatDefinition::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FStatDefinition.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FStatDefinition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStatDefinition, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("StatDefinition"));
	}
	return Z_Registration_Info_UScriptStruct_FStatDefinition.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FStatDefinition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatID_MetaData[] = {
		{ "Category", "Stat Definition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Stat'\xef\xbf\xbdn benzersiz kimli\xef\xbf\xbdi (ID). Kod i\xef\xbf\xbdinde bu ID ile stat'a eri\xef\xbf\xbd""ece\xef\xbf\xbdiz.\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stat'\xef\xbf\xbdn benzersiz kimli\xef\xbf\xbdi (ID). Kod i\xef\xbf\xbdinde bu ID ile stat'a eri\xef\xbf\xbd""ece\xef\xbf\xbdiz." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Stat Definition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The name to be displayed to the player in the stat. FText supports the game's localization.\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The name to be displayed to the player in the stat. FText supports the game's localization." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Stat Definition" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultValue_MetaData[] = {
		{ "Category", "Stat Definition" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_StatID;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStatDefinition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_StatID = { "StatID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStatDefinition, StatID), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatID_MetaData), NewProp_StatID_MetaData) }; // 133831994
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStatDefinition, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStatDefinition, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_DefaultValue = { "DefaultValue", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStatDefinition, DefaultValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultValue_MetaData), NewProp_DefaultValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FStatDefinition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_StatID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_DefaultValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatDefinition_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FStatDefinition_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"StatDefinition",
	Z_Construct_UScriptStruct_FStatDefinition_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatDefinition_Statics::PropPointers),
	sizeof(FStatDefinition),
	alignof(FStatDefinition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FStatDefinition_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FStatDefinition_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FStatDefinition()
{
	if (!Z_Registration_Info_UScriptStruct_FStatDefinition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStatDefinition.InnerSingleton, Z_Construct_UScriptStruct_FStatDefinition_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FStatDefinition.InnerSingleton;
}
// ********** End ScriptStruct FStatDefinition *****************************************************

// ********** Begin ScriptStruct FUpgradeEffect ****************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FUpgradeEffect;
class UScriptStruct* FUpgradeEffect::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FUpgradeEffect.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FUpgradeEffect.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FUpgradeEffect, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("UpgradeEffect"));
	}
	return Z_Registration_Info_UScriptStruct_FUpgradeEffect.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FUpgradeEffect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Represents a single effect that an upgrade can apply to a stat.\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Represents a single effect that an upgrade can apply to a stat." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetStat_MetaData[] = {
		{ "Category", "UpgradeEffect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Which stat does this effect modify?\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Which stat does this effect modify?" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Operation_MetaData[] = {
		{ "Category", "UpgradeEffect" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How is the value applied?\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How is the value applied?" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinMagnitude_MetaData[] = {
		{ "Category", "Value" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The magnitude of the effect will be a random value between Min and Max.\n// For a fixed value, set Min and Max to be the same.\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The magnitude of the effect will be a random value between Min and Max.\nFor a fixed value, set Min and Max to be the same." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxMagnitude_MetaData[] = {
		{ "Category", "Value" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetStat;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Operation_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Operation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinMagnitude;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxMagnitude;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FUpgradeEffect>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_TargetStat = { "TargetStat", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradeEffect, TargetStat), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetStat_MetaData), NewProp_TargetStat_MetaData) }; // 133831994
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_Operation_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_Operation = { "Operation", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradeEffect, Operation), Z_Construct_UEnum_ProjectRumble_EModifierOperation, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Operation_MetaData), NewProp_Operation_MetaData) }; // 139551574
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_MinMagnitude = { "MinMagnitude", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradeEffect, MinMagnitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinMagnitude_MetaData), NewProp_MinMagnitude_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_MaxMagnitude = { "MaxMagnitude", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradeEffect, MaxMagnitude), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxMagnitude_MetaData), NewProp_MaxMagnitude_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FUpgradeEffect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_TargetStat,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_Operation_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_Operation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_MinMagnitude,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewProp_MaxMagnitude,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradeEffect_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FUpgradeEffect_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
	nullptr,
	&NewStructOps,
	"UpgradeEffect",
	Z_Construct_UScriptStruct_FUpgradeEffect_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradeEffect_Statics::PropPointers),
	sizeof(FUpgradeEffect),
	alignof(FUpgradeEffect),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradeEffect_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FUpgradeEffect_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FUpgradeEffect()
{
	if (!Z_Registration_Info_UScriptStruct_FUpgradeEffect.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FUpgradeEffect.InnerSingleton, Z_Construct_UScriptStruct_FUpgradeEffect_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FUpgradeEffect.InnerSingleton;
}
// ********** End ScriptStruct FUpgradeEffect ******************************************************

// ********** Begin ScriptStruct FUpgradePoolEntry *************************************************
static_assert(std::is_polymorphic<FUpgradePoolEntry>() == std::is_polymorphic<FTableRowBase>(), "USTRUCT FUpgradePoolEntry cannot be polymorphic unless super FTableRowBase is polymorphic");
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FUpgradePoolEntry;
class UScriptStruct* FUpgradePoolEntry::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FUpgradePoolEntry, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("UpgradePoolEntry"));
	}
	return Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// An entry in an upgrade pool, used for random selection of upgrades.\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An entry in an upgrade pool, used for random selection of upgrades." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpgradeDataAsset_MetaData[] = {
		{ "Category", "UpgradePoolEntry" },
		{ "ModuleRelativePath", "Public/PRTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Weight_MetaData[] = {
		{ "Category", "UpgradePoolEntry" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// How likely is this upgrade to be picked? (Higher is more likely)\n" },
#endif
		{ "ModuleRelativePath", "Public/PRTypes.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How likely is this upgrade to be picked? (Higher is more likely)" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UpgradeDataAsset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Weight;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FUpgradePoolEntry>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::NewProp_UpgradeDataAsset = { "UpgradeDataAsset", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradePoolEntry, UpgradeDataAsset), Z_Construct_UClass_UPRUpgradeData_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpgradeDataAsset_MetaData), NewProp_UpgradeDataAsset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::NewProp_Weight = { "Weight", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FUpgradePoolEntry, Weight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Weight_MetaData), NewProp_Weight_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::NewProp_UpgradeDataAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::NewProp_Weight,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
	Z_Construct_UScriptStruct_FTableRowBase,
	&NewStructOps,
	"UpgradePoolEntry",
	Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::PropPointers),
	sizeof(FUpgradePoolEntry),
	alignof(FUpgradePoolEntry),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FUpgradePoolEntry()
{
	if (!Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.InnerSingleton, Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FUpgradePoolEntry.InnerSingleton;
}
// ********** End ScriptStruct FUpgradePoolEntry ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EFaction_StaticEnum, TEXT("EFaction"), &Z_Registration_Info_UEnum_EFaction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3868884884U) },
		{ EModifierOperation_StaticEnum, TEXT("EModifierOperation"), &Z_Registration_Info_UEnum_EModifierOperation, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 139551574U) },
		{ EUpgradeType_StaticEnum, TEXT("EUpgradeType"), &Z_Registration_Info_UEnum_EUpgradeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2071827181U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FStatDefinition::StaticStruct, Z_Construct_UScriptStruct_FStatDefinition_Statics::NewStructOps, TEXT("StatDefinition"), &Z_Registration_Info_UScriptStruct_FStatDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStatDefinition), 921955857U) },
		{ FUpgradeEffect::StaticStruct, Z_Construct_UScriptStruct_FUpgradeEffect_Statics::NewStructOps, TEXT("UpgradeEffect"), &Z_Registration_Info_UScriptStruct_FUpgradeEffect, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FUpgradeEffect), 4189924258U) },
		{ FUpgradePoolEntry::StaticStruct, Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics::NewStructOps, TEXT("UpgradePoolEntry"), &Z_Registration_Info_UScriptStruct_FUpgradePoolEntry, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FUpgradePoolEntry), 3330671521U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_1493042616(TEXT("/Script/ProjectRumble"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
