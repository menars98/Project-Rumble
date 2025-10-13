// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameModes/PRGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameMode();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRGameMode();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APRGameMode **************************************************************
void APRGameMode::StaticRegisterNativesAPRGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APRGameMode;
UClass* APRGameMode::GetPrivateStaticClass()
{
	using TClass = APRGameMode;
	if (!Z_Registration_Info_UClass_APRGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRGameMode"),
			Z_Registration_Info_UClass_APRGameMode.InnerSingleton,
			StaticRegisterNativesAPRGameMode,
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
	return Z_Registration_Info_UClass_APRGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_APRGameMode_NoRegister()
{
	return APRGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APRGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "GameModes/PRGameMode.h" },
		{ "ModuleRelativePath", "Public/GameModes/PRGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APRGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_APRGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameMode,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APRGameMode_Statics::ClassParams = {
	&APRGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APRGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_APRGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APRGameMode()
{
	if (!Z_Registration_Info_UClass_APRGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APRGameMode.OuterSingleton, Z_Construct_UClass_APRGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APRGameMode.OuterSingleton;
}
APRGameMode::APRGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(APRGameMode);
APRGameMode::~APRGameMode() {}
// ********** End Class APRGameMode ****************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APRGameMode, APRGameMode::StaticClass, TEXT("APRGameMode"), &Z_Registration_Info_UClass_APRGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APRGameMode), 360307386U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h__Script_ProjectRumble_2323829047(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
