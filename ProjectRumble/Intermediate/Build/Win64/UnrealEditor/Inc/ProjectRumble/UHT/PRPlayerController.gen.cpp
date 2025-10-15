// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Player/PRPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRPlayerController() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRPlayerController();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRPlayerController_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister();
UMG_API UClass* Z_Construct_UClass_UUserWidget_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APRPlayerController Function ApplyReward *********************************
struct Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics
{
	struct PRPlayerController_eventApplyReward_Parms
	{
		UPRUpgradeData* ChosenUpgrade;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called by the UI Widget when a player clicks on a reward button.\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called by the UI Widget when a player clicks on a reward button." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChosenUpgrade;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::NewProp_ChosenUpgrade = { "ChosenUpgrade", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRPlayerController_eventApplyReward_Parms, ChosenUpgrade), Z_Construct_UClass_UPRUpgradeData_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::NewProp_ChosenUpgrade,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APRPlayerController, nullptr, "ApplyReward", Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PropPointers), sizeof(Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PRPlayerController_eventApplyReward_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::Function_MetaDataParams), Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::PRPlayerController_eventApplyReward_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APRPlayerController_ApplyReward()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APRPlayerController_ApplyReward_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APRPlayerController::execApplyReward)
{
	P_GET_OBJECT(UPRUpgradeData,Z_Param_ChosenUpgrade);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyReward(Z_Param_ChosenUpgrade);
	P_NATIVE_END;
}
// ********** End Class APRPlayerController Function ApplyReward ***********************************

// ********** Begin Class APRPlayerController Function ShowLevelUpScreen ***************************
struct Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics
{
	struct PRPlayerController_eventShowLevelUpScreen_Parms
	{
		int32 NewLevel;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called by the StatsComponent's OnLevelUpDelegate.\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called by the StatsComponent's OnLevelUpDelegate." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::NewProp_NewLevel = { "NewLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRPlayerController_eventShowLevelUpScreen_Parms, NewLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::NewProp_NewLevel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APRPlayerController, nullptr, "ShowLevelUpScreen", Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PropPointers), sizeof(Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PRPlayerController_eventShowLevelUpScreen_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::Function_MetaDataParams), Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::PRPlayerController_eventShowLevelUpScreen_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APRPlayerController::execShowLevelUpScreen)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_NewLevel);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ShowLevelUpScreen(Z_Param_NewLevel);
	P_NATIVE_END;
}
// ********** End Class APRPlayerController Function ShowLevelUpScreen *****************************

// ********** Begin Class APRPlayerController ******************************************************
void APRPlayerController::StaticRegisterNativesAPRPlayerController()
{
	UClass* Class = APRPlayerController::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ApplyReward", &APRPlayerController::execApplyReward },
		{ "ShowLevelUpScreen", &APRPlayerController::execShowLevelUpScreen },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APRPlayerController;
UClass* APRPlayerController::GetPrivateStaticClass()
{
	using TClass = APRPlayerController;
	if (!Z_Registration_Info_UClass_APRPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRPlayerController"),
			Z_Registration_Info_UClass_APRPlayerController.InnerSingleton,
			StaticRegisterNativesAPRPlayerController,
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
	return Z_Registration_Info_UClass_APRPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_APRPlayerController_NoRegister()
{
	return APRPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APRPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Player/PRPlayerController.h" },
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RewardDataTable_MetaData[] = {
		{ "Category", "Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- REWARD SYSTEM --\n// The Data Table containing all possible stat upgrades (for the prototype).\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- REWARD SYSTEM --\nThe Data Table containing all possible stat upgrades (for the prototype)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OfferedRewards_MetaData[] = {
		{ "Category", "Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Array to hold the rewards that are currently being offered to the player.\n// We make it BlueprintReadOnly so the UI can read it.\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Array to hold the rewards that are currently being offered to the player.\nWe make it BlueprintReadOnly so the UI can read it." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelUpWidgetClass_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- UI --\n// The Level Up screen widget class. Assigned in the BP_PlayerController Blueprint.\n" },
#endif
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- UI --\nThe Level Up screen widget class. Assigned in the BP_PlayerController Blueprint." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelUpWidgetInstance_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// The instance of the level up screen, so we can remove it later.\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Player/PRPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The instance of the level up screen, so we can remove it later." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RewardDataTable;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OfferedRewards_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OfferedRewards;
	static const UECodeGen_Private::FClassPropertyParams NewProp_LevelUpWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LevelUpWidgetInstance;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APRPlayerController_ApplyReward, "ApplyReward" }, // 716020772
		{ &Z_Construct_UFunction_APRPlayerController_ShowLevelUpScreen, "ShowLevelUpScreen" }, // 2058455014
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APRPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRPlayerController_Statics::NewProp_RewardDataTable = { "RewardDataTable", nullptr, (EPropertyFlags)0x0124080000010005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRPlayerController, RewardDataTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RewardDataTable_MetaData), NewProp_RewardDataTable_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRPlayerController_Statics::NewProp_OfferedRewards_Inner = { "OfferedRewards", nullptr, (EPropertyFlags)0x0104000000020000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPRUpgradeData_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_APRPlayerController_Statics::NewProp_OfferedRewards = { "OfferedRewards", nullptr, (EPropertyFlags)0x0124080000020015, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRPlayerController, OfferedRewards), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OfferedRewards_MetaData), NewProp_OfferedRewards_MetaData) };
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_APRPlayerController_Statics::NewProp_LevelUpWidgetClass = { "LevelUpWidgetClass", nullptr, (EPropertyFlags)0x0024080000010005, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRPlayerController, LevelUpWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelUpWidgetClass_MetaData), NewProp_LevelUpWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_APRPlayerController_Statics::NewProp_LevelUpWidgetInstance = { "LevelUpWidgetInstance", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APRPlayerController, LevelUpWidgetInstance), Z_Construct_UClass_UUserWidget_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelUpWidgetInstance_MetaData), NewProp_LevelUpWidgetInstance_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APRPlayerController_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRPlayerController_Statics::NewProp_RewardDataTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRPlayerController_Statics::NewProp_OfferedRewards_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRPlayerController_Statics::NewProp_OfferedRewards,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRPlayerController_Statics::NewProp_LevelUpWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APRPlayerController_Statics::NewProp_LevelUpWidgetInstance,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRPlayerController_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APRPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APRPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APRPlayerController_Statics::ClassParams = {
	&APRPlayerController::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APRPlayerController_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APRPlayerController_Statics::PropPointers),
	0,
	0x009003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APRPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_APRPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APRPlayerController()
{
	if (!Z_Registration_Info_UClass_APRPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APRPlayerController.OuterSingleton, Z_Construct_UClass_APRPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APRPlayerController.OuterSingleton;
}
APRPlayerController::APRPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(APRPlayerController);
APRPlayerController::~APRPlayerController() {}
// ********** End Class APRPlayerController ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Player_PRPlayerController_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APRPlayerController, APRPlayerController::StaticClass, TEXT("APRPlayerController"), &Z_Registration_Info_UClass_APRPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APRPlayerController), 1707298379U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Player_PRPlayerController_h__Script_ProjectRumble_2059534405(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Player_PRPlayerController_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Player_PRPlayerController_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
