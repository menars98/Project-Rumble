// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Characters/PRCharacterBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRCharacterBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRCharacterBase();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRCharacterBase_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRCharacterDefinition_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APRCharacterBase *********************************************************
void APRCharacterBase::StaticRegisterNativesAPRCharacterBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APRCharacterBase;
UClass* APRCharacterBase::GetPrivateStaticClass()
{
	using TClass = APRCharacterBase;
	if (!Z_Registration_Info_UClass_APRCharacterBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRCharacterBase"),
			Z_Registration_Info_UClass_APRCharacterBase.InnerSingleton,
			StaticRegisterNativesAPRCharacterBase,
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
	return Z_Registration_Info_UClass_APRCharacterBase.InnerSingleton;
}
UClass* Z_Construct_UClass_APRCharacterBase_NoRegister()
{
	return APRCharacterBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APRCharacterBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Characters/PRCharacterBase.h" },
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContext_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- INPUT --\n// This is the main Input Mapping Context that will be loaded for gameplay.\n// It's assigned in the Blueprint derived from this class.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- INPUT --\nThis is the main Input Mapping Context that will be loaded for gameplay.\nIt's assigned in the Blueprint derived from this class." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Input Action for Movement (WASD). This is an asset reference.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for Movement (WASD). This is an asset reference." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Input Action for Looking around (Mouse). This is an asset reference.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for Looking around (Mouse). This is an asset reference." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Input Action for Jumping.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for Jumping." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DebugDamageAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Input Action for Debug Damage (for testing purposes).\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Action for Debug Damage (for testing purposes)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArmComp_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- COMPONENTS --\n// The Spring Arm (or camera boom) positions the camera behind the character.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- COMPONENTS --\nThe Spring Arm (or camera boom) positions the camera behind the character." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraComp_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The camera that follows the character.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The camera that follows the character." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPitchMin_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The lowest angle the camera can look down to, in degrees. */" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The lowest angle the camera can look down to, in degrees." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPitchMax_MetaData[] = {
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The highest angle the camera can look up to, in degrees. */" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The highest angle the camera can look up to, in degrees." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterDefinition_MetaData[] = {
		{ "Category", "Character" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- CHARACTER DATA --\n// This holds the data asset that defines this character's identity (mesh, stats, etc.)\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- CHARACTER DATA --\nThis holds the data asset that defines this character's identity (mesh, stats, etc.)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CachedStatsComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The cached pointer for performance now lives here, where it's needed.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Characters/PRCharacterBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The cached pointer for performance now lives here, where it's needed." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContext;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DebugDamageAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArmComp;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraComp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraPitchMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraPitchMax;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterDefinition;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CachedStatsComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APRCharacterBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_DefaultMappingContext = { "DefaultMappingContext", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, DefaultMappingContext), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContext_MetaData), NewProp_DefaultMappingContext_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, MoveAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, LookAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, JumpAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_DebugDamageAction = { "DebugDamageAction", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, DebugDamageAction), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DebugDamageAction_MetaData), NewProp_DebugDamageAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_SpringArmComp = { "SpringArmComp", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, SpringArmComp), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArmComp_MetaData), NewProp_SpringArmComp_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraComp = { "CameraComp", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, CameraComp), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraComp_MetaData), NewProp_CameraComp_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraPitchMin = { "CameraPitchMin", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, CameraPitchMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPitchMin_MetaData), NewProp_CameraPitchMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraPitchMax = { "CameraPitchMax", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, CameraPitchMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPitchMax_MetaData), NewProp_CameraPitchMax_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CharacterDefinition = { "CharacterDefinition", nullptr, (EPropertyFlags)0x0124080000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, CharacterDefinition), Z_Construct_UClass_UPRCharacterDefinition_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterDefinition_MetaData), NewProp_CharacterDefinition_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CachedStatsComponent = { "CachedStatsComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRCharacterBase, CachedStatsComponent), Z_Construct_UClass_UPRStatsComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CachedStatsComponent_MetaData), NewProp_CachedStatsComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APRCharacterBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_DefaultMappingContext,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_DebugDamageAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_SpringArmComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraPitchMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CameraPitchMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CharacterDefinition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRCharacterBase_Statics::NewProp_CachedStatsComponent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRCharacterBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APRCharacterBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APREntityBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRCharacterBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APRCharacterBase_Statics::ClassParams = {
	&APRCharacterBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APRCharacterBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APRCharacterBase_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APRCharacterBase_Statics::Class_MetaDataParams), Z_Construct_UClass_APRCharacterBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APRCharacterBase()
{
	if (!Z_Registration_Info_UClass_APRCharacterBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APRCharacterBase.OuterSingleton, Z_Construct_UClass_APRCharacterBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APRCharacterBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APRCharacterBase);
APRCharacterBase::~APRCharacterBase() {}
// ********** End Class APRCharacterBase ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APRCharacterBase, APRCharacterBase::StaticClass, TEXT("APRCharacterBase"), &Z_Registration_Info_UClass_APRCharacterBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APRCharacterBase), 2734608352U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h__Script_ProjectRumble_3012636606(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
