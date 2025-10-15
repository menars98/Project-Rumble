// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Managers/PRRewardManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRRewardManager() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRInventoryComponent_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRRewardManager();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRRewardManager_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UPRRewardManager Function GenerateAndDraftRewards ************************
struct Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics
{
	struct PRRewardManager_eventGenerateAndDraftRewards_Parms
	{
		TArray<UDataTable*> AllUpgradePools;
		const UPRInventoryComponent* PlayerInventory;
		int32 NumOfChoices;
		TArray<UPRUpgradeData*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Rewards" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Main function to generate and draft a list of rewards for the player.\n\x09 * @param AllUpgradePools An array of Data Tables to draw rewards from.\n\x09 * @param PlayerInventory A reference to the player's inventory to check current items.\n\x09 * @param NumOfChoices The number of rewards to offer the player.\n\x09 * @return An array of offered upgrade data assets.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Managers/PRRewardManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Main function to generate and draft a list of rewards for the player.\n@param AllUpgradePools An array of Data Tables to draw rewards from.\n@param PlayerInventory A reference to the player's inventory to check current items.\n@param NumOfChoices The number of rewards to offer the player.\n@return An array of offered upgrade data assets." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AllUpgradePools_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlayerInventory_MetaData[] = {
		{ "EditInline", "true" },
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AllUpgradePools_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AllUpgradePools;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerInventory;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumOfChoices;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_AllUpgradePools_Inner = { "AllUpgradePools", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_AllUpgradePools = { "AllUpgradePools", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRRewardManager_eventGenerateAndDraftRewards_Parms, AllUpgradePools), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AllUpgradePools_MetaData), NewProp_AllUpgradePools_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_PlayerInventory = { "PlayerInventory", nullptr, (EPropertyFlags)0x0010000000080082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRRewardManager_eventGenerateAndDraftRewards_Parms, PlayerInventory), Z_Construct_UClass_UPRInventoryComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlayerInventory_MetaData), NewProp_PlayerInventory_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_NumOfChoices = { "NumOfChoices", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRRewardManager_eventGenerateAndDraftRewards_Parms, NumOfChoices), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UPRUpgradeData_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRRewardManager_eventGenerateAndDraftRewards_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_AllUpgradePools_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_AllUpgradePools,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_PlayerInventory,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_NumOfChoices,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRRewardManager, nullptr, "GenerateAndDraftRewards", Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PRRewardManager_eventGenerateAndDraftRewards_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::PRRewardManager_eventGenerateAndDraftRewards_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRRewardManager::execGenerateAndDraftRewards)
{
	P_GET_TARRAY_REF(UDataTable*,Z_Param_Out_AllUpgradePools);
	P_GET_OBJECT(UPRInventoryComponent,Z_Param_PlayerInventory);
	P_GET_PROPERTY(FIntProperty,Z_Param_NumOfChoices);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<UPRUpgradeData*>*)Z_Param__Result=P_THIS->GenerateAndDraftRewards(Z_Param_Out_AllUpgradePools,Z_Param_PlayerInventory,Z_Param_NumOfChoices);
	P_NATIVE_END;
}
// ********** End Class UPRRewardManager Function GenerateAndDraftRewards **************************

// ********** Begin Class UPRRewardManager *********************************************************
void UPRRewardManager::StaticRegisterNativesUPRRewardManager()
{
	UClass* Class = UPRRewardManager::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GenerateAndDraftRewards", &UPRRewardManager::execGenerateAndDraftRewards },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPRRewardManager;
UClass* UPRRewardManager::GetPrivateStaticClass()
{
	using TClass = UPRRewardManager;
	if (!Z_Registration_Info_UClass_UPRRewardManager.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRRewardManager"),
			Z_Registration_Info_UClass_UPRRewardManager.InnerSingleton,
			StaticRegisterNativesUPRRewardManager,
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
	return Z_Registration_Info_UClass_UPRRewardManager.InnerSingleton;
}
UClass* Z_Construct_UClass_UPRRewardManager_NoRegister()
{
	return UPRRewardManager::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPRRewardManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Manages the logic for generating and drafting level-up rewards.\n *  This is a transient UObject, created when needed.\n */" },
#endif
		{ "IncludePath", "Managers/PRRewardManager.h" },
		{ "ModuleRelativePath", "Public/Managers/PRRewardManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manages the logic for generating and drafting level-up rewards.\nThis is a transient UObject, created when needed." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UPRRewardManager_GenerateAndDraftRewards, "GenerateAndDraftRewards" }, // 3066085153
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPRRewardManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UPRRewardManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRRewardManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPRRewardManager_Statics::ClassParams = {
	&UPRRewardManager::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPRRewardManager_Statics::Class_MetaDataParams), Z_Construct_UClass_UPRRewardManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPRRewardManager()
{
	if (!Z_Registration_Info_UClass_UPRRewardManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPRRewardManager.OuterSingleton, Z_Construct_UClass_UPRRewardManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPRRewardManager.OuterSingleton;
}
UPRRewardManager::UPRRewardManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPRRewardManager);
UPRRewardManager::~UPRRewardManager() {}
// ********** End Class UPRRewardManager ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPRRewardManager, UPRRewardManager::StaticClass, TEXT("UPRRewardManager"), &Z_Registration_Info_UClass_UPRRewardManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPRRewardManager), 184092016U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h__Script_ProjectRumble_2636348991(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
