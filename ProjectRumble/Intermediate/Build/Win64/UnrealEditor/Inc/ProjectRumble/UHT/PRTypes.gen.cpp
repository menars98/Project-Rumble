// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PRTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRTypes() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FTableRowBase();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EFaction();
PROJECTRUMBLE_API UScriptStruct* Z_Construct_UScriptStruct_FStatDefinition();
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
	static const UECodeGen_Private::FNamePropertyParams NewProp_StatID;
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
const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FStatDefinition_Statics::NewProp_StatID = { "StatID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FStatDefinition, StatID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatID_MetaData), NewProp_StatID_MetaData) };
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

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EFaction_StaticEnum, TEXT("EFaction"), &Z_Registration_Info_UEnum_EFaction, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3868884884U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FStatDefinition::StaticStruct, Z_Construct_UScriptStruct_FStatDefinition_Statics::NewStructOps, TEXT("StatDefinition"), &Z_Registration_Info_UScriptStruct_FStatDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStatDefinition), 757954916U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_640857011(TEXT("/Script/ProjectRumble"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h__Script_ProjectRumble_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
