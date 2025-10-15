// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AI/PRAIBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRAIBase() {}

// ********** Begin Cross Module References ********************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRAIBase();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRAIBase_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APRAIBase ****************************************************************
void APRAIBase::StaticRegisterNativesAPRAIBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APRAIBase;
UClass* APRAIBase::GetPrivateStaticClass()
{
	using TClass = APRAIBase;
	if (!Z_Registration_Info_UClass_APRAIBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRAIBase"),
			Z_Registration_Info_UClass_APRAIBase.InnerSingleton,
			StaticRegisterNativesAPRAIBase,
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
	return Z_Registration_Info_UClass_APRAIBase.InnerSingleton;
}
UClass* Z_Construct_UClass_APRAIBase_NoRegister()
{
	return APRAIBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APRAIBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AI/PRAIBase.h" },
		{ "ModuleRelativePath", "Public/AI/PRAIBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatsComponent_AI_MetaData[] = {
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- COMPONENTS --\n// The AI has its own StatsComponent directly on itself.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AI/PRAIBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- COMPONENTS --\nThe AI has its own StatsComponent directly on itself." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_XPToAward_MetaData[] = {
		{ "Category", "Loot" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The amount of XP this AI drops when it dies.\n" },
#endif
		{ "ModuleRelativePath", "Public/AI/PRAIBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The amount of XP this AI drops when it dies." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatsComponent_AI;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_XPToAward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APRAIBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRAIBase_Statics::NewProp_StatsComponent_AI = { "StatsComponent_AI", nullptr, (EPropertyFlags)0x01240800000a001d, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRAIBase, StatsComponent_AI), Z_Construct_UClass_UPRStatsComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatsComponent_AI_MetaData), NewProp_StatsComponent_AI_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_APRAIBase_Statics::NewProp_XPToAward = { "XPToAward", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRAIBase, XPToAward), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_XPToAward_MetaData), NewProp_XPToAward_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APRAIBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRAIBase_Statics::NewProp_StatsComponent_AI,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRAIBase_Statics::NewProp_XPToAward,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRAIBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APRAIBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APREntityBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRAIBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APRAIBase_Statics::ClassParams = {
	&APRAIBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APRAIBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APRAIBase_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APRAIBase_Statics::Class_MetaDataParams), Z_Construct_UClass_APRAIBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APRAIBase()
{
	if (!Z_Registration_Info_UClass_APRAIBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APRAIBase.OuterSingleton, Z_Construct_UClass_APRAIBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APRAIBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APRAIBase);
APRAIBase::~APRAIBase() {}
// ********** End Class APRAIBase ******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APRAIBase, APRAIBase::StaticClass, TEXT("APRAIBase"), &Z_Registration_Info_UClass_APRAIBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APRAIBase), 3299791524U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h__Script_ProjectRumble_4141211659(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
