// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "UI/PRHUD.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRHUD() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AHUD();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRHUD();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRHUD_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APRHUD *******************************************************************
void APRHUD::StaticRegisterNativesAPRHUD()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_APRHUD;
UClass* APRHUD::GetPrivateStaticClass()
{
	using TClass = APRHUD;
	if (!Z_Registration_Info_UClass_APRHUD.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRHUD"),
			Z_Registration_Info_UClass_APRHUD.InnerSingleton,
			StaticRegisterNativesAPRHUD,
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
	return Z_Registration_Info_UClass_APRHUD.InnerSingleton;
}
UClass* Z_Construct_UClass_APRHUD_NoRegister()
{
	return APRHUD::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APRHUD_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Rendering Actor Input Replication" },
		{ "IncludePath", "UI/PRHUD.h" },
		{ "ModuleRelativePath", "Public/UI/PRHUD.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerHUDWidgetClass_MetaData[] = {
		{ "Category", "Widgets" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The main gameplay widget class to create.\n// We assign this in the Blueprint derived from this class.\n" },
#endif
		{ "ModuleRelativePath", "Public/UI/PRHUD.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The main gameplay widget class to create.\nWe assign this in the Blueprint derived from this class." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerHUDWidget_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The instance of our main gameplay widget.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/UI/PRHUD.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The instance of our main gameplay widget." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_PlayerHUDWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerHUDWidget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APRHUD>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_APRHUD_Statics::NewProp_PlayerHUDWidgetClass = { "PlayerHUDWidgetClass", nullptr, (EPropertyFlags)0x0024080000010001, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRHUD, PlayerHUDWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerHUDWidgetClass_MetaData), NewProp_PlayerHUDWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRHUD_Statics::NewProp_PlayerHUDWidget = { "PlayerHUDWidget", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRHUD, PlayerHUDWidget), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerHUDWidget_MetaData), NewProp_PlayerHUDWidget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APRHUD_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRHUD_Statics::NewProp_PlayerHUDWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRHUD_Statics::NewProp_PlayerHUDWidget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRHUD_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APRHUD_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AHUD,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRHUD_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APRHUD_Statics::ClassParams = {
	&APRHUD::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_APRHUD_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_APRHUD_Statics::PropPointers),
	0,
	0x009003ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APRHUD_Statics::Class_MetaDataParams), Z_Construct_UClass_APRHUD_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APRHUD()
{
	if (!Z_Registration_Info_UClass_APRHUD.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APRHUD.OuterSingleton, Z_Construct_UClass_APRHUD_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APRHUD.OuterSingleton;
}
APRHUD::APRHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(APRHUD);
APRHUD::~APRHUD() {}
// ********** End Class APRHUD *********************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APRHUD, APRHUD::StaticClass, TEXT("APRHUD"), &Z_Registration_Info_UClass_APRHUD, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APRHUD), 933447580U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h__Script_ProjectRumble_2711738952(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
