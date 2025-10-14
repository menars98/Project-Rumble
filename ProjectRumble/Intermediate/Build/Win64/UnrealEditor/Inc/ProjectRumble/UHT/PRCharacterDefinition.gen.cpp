// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Datas/PRCharacterDefinition.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRCharacterDefinition() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_UAnimInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USkeletalMesh_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRCharacterDefinition();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRCharacterDefinition_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UPRCharacterDefinition ***************************************************
void UPRCharacterDefinition::StaticRegisterNativesUPRCharacterDefinition()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPRCharacterDefinition;
UClass* UPRCharacterDefinition::GetPrivateStaticClass()
{
	using TClass = UPRCharacterDefinition;
	if (!Z_Registration_Info_UClass_UPRCharacterDefinition.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRCharacterDefinition"),
			Z_Registration_Info_UClass_UPRCharacterDefinition.InnerSingleton,
			StaticRegisterNativesUPRCharacterDefinition,
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
	return Z_Registration_Info_UClass_UPRCharacterDefinition.InnerSingleton;
}
UClass* Z_Construct_UClass_UPRCharacterDefinition_NoRegister()
{
	return UPRCharacterDefinition::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPRCharacterDefinition_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data Asset that defines the properties for a playable character.\n * This holds all static, unchanging data for a character like its mesh, stats, and abilities.\n */" },
#endif
		{ "IncludePath", "Datas/PRCharacterDefinition.h" },
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data Asset that defines the properties for a playable character.\nThis holds all static, unchanging data for a character like its mesh, stats, and abilities." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterName_MetaData[] = {
		{ "Category", "Visuals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The unique name of this character. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The unique name of this character." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterDescription_MetaData[] = {
		{ "Category", "Visuals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** A brief description of the character for the selection screen. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
		{ "MultiLine", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A brief description of the character for the selection screen." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterMesh_MetaData[] = {
		{ "Category", "Visuals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The skeletal mesh to use for this character. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The skeletal mesh to use for this character." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AnimationBlueprintClass_MetaData[] = {
		{ "Category", "Visuals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The animation blueprint class to use for this character. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The animation blueprint class to use for this character." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterIcon_MetaData[] = {
		{ "Category", "Visuals" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The icon displayed for this character in UI. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The icon displayed for this character in UI." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartingStatsTable_MetaData[] = {
		{ "Category", "Stats" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The Data Table containing the initial stat values for this character. */" },
#endif
		{ "ModuleRelativePath", "Public/Datas/PRCharacterDefinition.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The Data Table containing the initial stat values for this character." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_CharacterName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_CharacterDescription;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterMesh;
	static const UECodeGen_Private::FClassPropertyParams NewProp_AnimationBlueprintClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterIcon;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StartingStatsTable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPRCharacterDefinition>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterName = { "CharacterName", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, CharacterName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterName_MetaData), NewProp_CharacterName_MetaData) };
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterDescription = { "CharacterDescription", nullptr, (EPropertyFlags)0x0010000000010015, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, CharacterDescription), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterDescription_MetaData), NewProp_CharacterDescription_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterMesh = { "CharacterMesh", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, CharacterMesh), Z_Construct_UClass_USkeletalMesh_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterMesh_MetaData), NewProp_CharacterMesh_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_AnimationBlueprintClass = { "AnimationBlueprintClass", nullptr, (EPropertyFlags)0x0014000000010015, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, AnimationBlueprintClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AnimationBlueprintClass_MetaData), NewProp_AnimationBlueprintClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterIcon = { "CharacterIcon", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, CharacterIcon), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterIcon_MetaData), NewProp_CharacterIcon_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_StartingStatsTable = { "StartingStatsTable", nullptr, (EPropertyFlags)0x0114000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRCharacterDefinition, StartingStatsTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartingStatsTable_MetaData), NewProp_StartingStatsTable_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPRCharacterDefinition_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterDescription,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_AnimationBlueprintClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_CharacterIcon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRCharacterDefinition_Statics::NewProp_StartingStatsTable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRCharacterDefinition_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPRCharacterDefinition_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRCharacterDefinition_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPRCharacterDefinition_Statics::ClassParams = {
	&UPRCharacterDefinition::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UPRCharacterDefinition_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UPRCharacterDefinition_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPRCharacterDefinition_Statics::Class_MetaDataParams), Z_Construct_UClass_UPRCharacterDefinition_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPRCharacterDefinition()
{
	if (!Z_Registration_Info_UClass_UPRCharacterDefinition.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPRCharacterDefinition.OuterSingleton, Z_Construct_UClass_UPRCharacterDefinition_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPRCharacterDefinition.OuterSingleton;
}
UPRCharacterDefinition::UPRCharacterDefinition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPRCharacterDefinition);
UPRCharacterDefinition::~UPRCharacterDefinition() {}
// ********** End Class UPRCharacterDefinition *****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRCharacterDefinition_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPRCharacterDefinition, UPRCharacterDefinition::StaticClass, TEXT("UPRCharacterDefinition"), &Z_Registration_Info_UClass_UPRCharacterDefinition, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPRCharacterDefinition), 3215660565U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRCharacterDefinition_h__Script_ProjectRumble_3759235573(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRCharacterDefinition_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRCharacterDefinition_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
