// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Datas/PRUpgradeData.h"
#include "PRTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRUpgradeData() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EUpgradeRarity();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EUpgradeType();
PROJECTRUMBLE_API UScriptStruct* Z_Construct_UScriptStruct_FUpgradeEffect();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EUpgradeRarity ************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EUpgradeRarity;
static UEnum* EUpgradeRarity_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EUpgradeRarity.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EUpgradeRarity.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_ProjectRumble_EUpgradeRarity, (UObject*)Z_Construct_UPackage__Script_ProjectRumble(), TEXT("EUpgradeRarity"));
	}
	return Z_Registration_Info_UEnum_EUpgradeRarity.OuterSingleton;
}
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EUpgradeRarity>()
{
	return EUpgradeRarity_StaticEnum();
}
struct Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Common.Name", "EUpgradeRarity::Common" },
		{ "Epic.Name", "EUpgradeRarity::Epic" },
		{ "Legendary.Name", "EUpgradeRarity::Legendary" },
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
		{ "Rare.Name", "EUpgradeRarity::Rare" },
		{ "Uncommon.Name", "EUpgradeRarity::Uncommon" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EUpgradeRarity::Common", (int64)EUpgradeRarity::Common },
		{ "EUpgradeRarity::Uncommon", (int64)EUpgradeRarity::Uncommon },
		{ "EUpgradeRarity::Rare", (int64)EUpgradeRarity::Rare },
		{ "EUpgradeRarity::Epic", (int64)EUpgradeRarity::Epic },
		{ "EUpgradeRarity::Legendary", (int64)EUpgradeRarity::Legendary },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble,
	nullptr,
	"EUpgradeRarity",
	"EUpgradeRarity",
	Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::Enum_MetaDataParams), Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_ProjectRumble_EUpgradeRarity()
{
	if (!Z_Registration_Info_UEnum_EUpgradeRarity.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EUpgradeRarity.InnerSingleton, Z_Construct_UEnum_ProjectRumble_EUpgradeRarity_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EUpgradeRarity.InnerSingleton;
}
// ********** End Enum EUpgradeRarity **************************************************************

// ********** Begin Class UPRUpgradeData ***********************************************************
void UPRUpgradeData::StaticRegisterNativesUPRUpgradeData()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPRUpgradeData;
UClass* UPRUpgradeData::GetPrivateStaticClass()
{
	using TClass = UPRUpgradeData;
	if (!Z_Registration_Info_UClass_UPRUpgradeData.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRUpgradeData"),
			Z_Registration_Info_UClass_UPRUpgradeData.InnerSingleton,
			StaticRegisterNativesUPRUpgradeData,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UPRUpgradeData.InnerSingleton;
}
UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister()
{
	return UPRUpgradeData::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPRUpgradeData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "Datas/PRUpgradeData.h" },
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UpgradeType_MetaData[] = {
		{ "Category", "Upgrade" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The type of this upgrade. This determines how it will be applied.\n" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The type of this upgrade. This determines how it will be applied." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Upgrade" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The text displayed on the reward card.\n" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The text displayed on the reward card." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Upgrade" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A more detailed description of what this upgrade does.\n" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A more detailed description of what this upgrade does." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Icon_MetaData[] = {
		{ "Category", "Upgrade" },
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ItemClass_MetaData[] = {
		{ "Category", "Upgrade Data" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- DATA FOR SPECIFIC UPGRADE TYPES ---\n// Which Weapon or Passive Item class does this upgrade relate to?\n// Used for 'NewWeapon', 'UpgradeWeapon', 'NewPassiveItem', 'UpgradePassiveItem'.\n" },
#endif
		{ "EditCondition", "UpgradeType != EUpgradeType::StatBonus" },
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- DATA FOR SPECIFIC UPGRADE TYPES ---\nWhich Weapon or Passive Item class does this upgrade relate to?\nUsed for 'NewWeapon', 'UpgradeWeapon', 'NewPassiveItem', 'UpgradePassiveItem'." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rarity_MetaData[] = {
		{ "Category", "Upgrade" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The rarity of this upgrade. This can affect its values and appearance.\n" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The rarity of this upgrade. This can affect its values and appearance." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Effects_MetaData[] = {
		{ "Category", "Upgrade" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This array holds all the effects this upgrade will apply.\n// A single upgrade can now modify multiple stats at once.\n" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRUpgradeData.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This array holds all the effects this upgrade will apply.\nA single upgrade can now modify multiple stats at once." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_UpgradeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_UpgradeType;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Icon;
	static const UECodeGen_Private::FClassPropertyParams NewProp_ItemClass;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Rarity_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Rarity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Effects_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Effects;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPRUpgradeData>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_UpgradeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_UpgradeType = { "UpgradeType", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, UpgradeType), Z_Construct_UEnum_ProjectRumble_EUpgradeType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UpgradeType_MetaData), NewProp_UpgradeType_MetaData) }; // 2071827181
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Icon = { "Icon", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, Icon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Icon_MetaData), NewProp_Icon_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_ItemClass = { "ItemClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, ItemClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ItemClass_MetaData), NewProp_ItemClass_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Rarity_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Rarity = { "Rarity", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, Rarity), Z_Construct_UEnum_ProjectRumble_EUpgradeRarity, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rarity_MetaData), NewProp_Rarity_MetaData) }; // 897432342
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Effects_Inner = { "Effects", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FUpgradeEffect, METADATA_PARAMS(0, nullptr) }; // 4189924258
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Effects = { "Effects", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRUpgradeData, Effects), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Effects_MetaData), NewProp_Effects_MetaData) }; // 4189924258
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPRUpgradeData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_UpgradeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_UpgradeType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Icon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_ItemClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Rarity_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Rarity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Effects_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRUpgradeData_Statics::NewProp_Effects,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRUpgradeData_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPRUpgradeData_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRUpgradeData_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPRUpgradeData_Statics::ClassParams = {
	&UPRUpgradeData::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UPRUpgradeData_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UPRUpgradeData_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPRUpgradeData_Statics::Class_MetaDataParams), Z_Construct_UClass_UPRUpgradeData_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPRUpgradeData()
{
	if (!Z_Registration_Info_UClass_UPRUpgradeData.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPRUpgradeData.OuterSingleton, Z_Construct_UClass_UPRUpgradeData_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPRUpgradeData.OuterSingleton;
}
UPRUpgradeData::UPRUpgradeData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPRUpgradeData);
UPRUpgradeData::~UPRUpgradeData() {}
// ********** End Class UPRUpgradeData *************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EUpgradeRarity_StaticEnum, TEXT("EUpgradeRarity"), &Z_Registration_Info_UEnum_EUpgradeRarity, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 897432342U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPRUpgradeData, UPRUpgradeData::StaticClass, TEXT("UPRUpgradeData"), &Z_Registration_Info_UClass_UPRUpgradeData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPRUpgradeData), 1354069948U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_3392852785(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h__Script_ProjectRumble_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
