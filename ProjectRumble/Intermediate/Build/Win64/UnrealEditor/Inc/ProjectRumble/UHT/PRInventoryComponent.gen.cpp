// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Components/PRInventoryComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRInventoryComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRInventoryComponent();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRInventoryComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UPRInventoryComponent ****************************************************
void UPRInventoryComponent::StaticRegisterNativesUPRInventoryComponent()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPRInventoryComponent;
UClass* UPRInventoryComponent::GetPrivateStaticClass()
{
	using TClass = UPRInventoryComponent;
	if (!Z_Registration_Info_UClass_UPRInventoryComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRInventoryComponent"),
			Z_Registration_Info_UClass_UPRInventoryComponent.InnerSingleton,
			StaticRegisterNativesUPRInventoryComponent,
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
	return Z_Registration_Info_UClass_UPRInventoryComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UPRInventoryComponent_NoRegister()
{
	return UPRInventoryComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPRInventoryComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Components/PRInventoryComponent.h" },
		{ "ModuleRelativePath", "Public/Components/PRInventoryComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPRInventoryComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UPRInventoryComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRInventoryComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPRInventoryComponent_Statics::ClassParams = {
	&UPRInventoryComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPRInventoryComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UPRInventoryComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPRInventoryComponent()
{
	if (!Z_Registration_Info_UClass_UPRInventoryComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPRInventoryComponent.OuterSingleton, Z_Construct_UClass_UPRInventoryComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPRInventoryComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPRInventoryComponent);
UPRInventoryComponent::~UPRInventoryComponent() {}
// ********** End Class UPRInventoryComponent ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRInventoryComponent_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPRInventoryComponent, UPRInventoryComponent::StaticClass, TEXT("UPRInventoryComponent"), &Z_Registration_Info_UClass_UPRInventoryComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPRInventoryComponent), 4258516839U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRInventoryComponent_h__Script_ProjectRumble_2469185906(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRInventoryComponent_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRInventoryComponent_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
