// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Components/PRStatsComponent.h"
#include "GameplayTagContainer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePRStatsComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UDataTable_NoRegister();
GAMEPLAYTAGS_API UScriptStruct* Z_Construct_UScriptStruct_FGameplayTag();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister();
PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature();
PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature();
PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature();
PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature();
PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FOnStatChangedSignature ***********************************************
struct Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics
{
	struct _Script_ProjectRumble_eventOnStatChangedSignature_Parms
	{
		FGameplayTag StatTag;
		float NewValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This delegate will broadcast when any stat changes, sending the StatTag and its new value.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This delegate will broadcast when any stat changes, sending the StatTag and its new value." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_StatTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::NewProp_StatTag = { "StatTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnStatChangedSignature_Parms, StatTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(0, nullptr) }; // 133831994
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnStatChangedSignature_Parms, NewValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::NewProp_StatTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::NewProp_NewValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble, nullptr, "OnStatChangedSignature__DelegateSignature", Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnStatChangedSignature_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnStatChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnStatChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnStatChangedSignature, FGameplayTag StatTag, float NewValue)
{
	struct _Script_ProjectRumble_eventOnStatChangedSignature_Parms
	{
		FGameplayTag StatTag;
		float NewValue;
	};
	_Script_ProjectRumble_eventOnStatChangedSignature_Parms Parms;
	Parms.StatTag=StatTag;
	Parms.NewValue=NewValue;
	OnStatChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnStatChangedSignature *************************************************

// ********** Begin Delegate FOnXPChangedSignature *************************************************
struct Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics
{
	struct _Script_ProjectRumble_eventOnXPChangedSignature_Parms
	{
		float CurrentXP;
		float MaxXP;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This delegate will broadcast when XP changes, sending the current and max XP.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This delegate will broadcast when XP changes, sending the current and max XP." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentXP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxXP;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::NewProp_CurrentXP = { "CurrentXP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnXPChangedSignature_Parms, CurrentXP), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::NewProp_MaxXP = { "MaxXP", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnXPChangedSignature_Parms, MaxXP), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::NewProp_CurrentXP,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::NewProp_MaxXP,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble, nullptr, "OnXPChangedSignature__DelegateSignature", Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnXPChangedSignature_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnXPChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnXPChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnXPChangedSignature, float CurrentXP, float MaxXP)
{
	struct _Script_ProjectRumble_eventOnXPChangedSignature_Parms
	{
		float CurrentXP;
		float MaxXP;
	};
	_Script_ProjectRumble_eventOnXPChangedSignature_Parms Parms;
	Parms.CurrentXP=CurrentXP;
	Parms.MaxXP=MaxXP;
	OnXPChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnXPChangedSignature ***************************************************

// ********** Begin Delegate FOnHealthChangedSignature *********************************************
struct Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics
{
	struct _Script_ProjectRumble_eventOnHealthChangedSignature_Parms
	{
		float CurrentHealth;
		float MaxHealth;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This delegate will broadcast when health changes, sending the current and max health.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This delegate will broadcast when health changes, sending the current and max health." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::NewProp_CurrentHealth = { "CurrentHealth", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnHealthChangedSignature_Parms, CurrentHealth), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnHealthChangedSignature_Parms, MaxHealth), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::NewProp_CurrentHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::NewProp_MaxHealth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble, nullptr, "OnHealthChangedSignature__DelegateSignature", Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnHealthChangedSignature_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnHealthChangedSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnHealthChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHealthChangedSignature, float CurrentHealth, float MaxHealth)
{
	struct _Script_ProjectRumble_eventOnHealthChangedSignature_Parms
	{
		float CurrentHealth;
		float MaxHealth;
	};
	_Script_ProjectRumble_eventOnHealthChangedSignature_Parms Parms;
	Parms.CurrentHealth=CurrentHealth;
	Parms.MaxHealth=MaxHealth;
	OnHealthChangedSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnHealthChangedSignature ***********************************************

// ********** Begin Delegate FOnDeathSignature *****************************************************
struct Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This delegate will broadcast when the owner's health reaches zero.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This delegate will broadcast when the owner's health reaches zero." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble, nullptr, "OnDeathSignature__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnDeathSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDeathSignature)
{
	OnDeathSignature.ProcessMulticastDelegate<UObject>(NULL);
}
// ********** End Delegate FOnDeathSignature *******************************************************

// ********** Begin Delegate FOnLevelUpSignature ***************************************************
struct Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics
{
	struct _Script_ProjectRumble_eventOnLevelUpSignature_Parms
	{
		int32 NewLevel;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This delegate will broadcast when the owner levels up, sending the new level.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This delegate will broadcast when the owner levels up, sending the new level." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewLevel;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::NewProp_NewLevel = { "NewLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_ProjectRumble_eventOnLevelUpSignature_Parms, NewLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::NewProp_NewLevel,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_ProjectRumble, nullptr, "OnLevelUpSignature__DelegateSignature", Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnLevelUpSignature_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::_Script_ProjectRumble_eventOnLevelUpSignature_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FOnLevelUpSignature_DelegateWrapper(const FMulticastScriptDelegate& OnLevelUpSignature, int32 NewLevel)
{
	struct _Script_ProjectRumble_eventOnLevelUpSignature_Parms
	{
		int32 NewLevel;
	};
	_Script_ProjectRumble_eventOnLevelUpSignature_Parms Parms;
	Parms.NewLevel=NewLevel;
	OnLevelUpSignature.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FOnLevelUpSignature *****************************************************

// ********** Begin Class UPRStatsComponent Function AddXP *****************************************
struct Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics
{
	struct PRStatsComponent_eventAddXP_Parms
	{
		float XPAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Stats" },
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_XPAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::NewProp_XPAmount = { "XPAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventAddXP_Parms, XPAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::NewProp_XPAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRStatsComponent, nullptr, "AddXP", Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PRStatsComponent_eventAddXP_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::PRStatsComponent_eventAddXP_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPRStatsComponent_AddXP()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRStatsComponent_AddXP_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRStatsComponent::execAddXP)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_XPAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AddXP(Z_Param_XPAmount);
	P_NATIVE_END;
}
// ********** End Class UPRStatsComponent Function AddXP *******************************************

// ********** Begin Class UPRStatsComponent Function ApplyDamage ***********************************
struct Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics
{
	struct PRStatsComponent_eventApplyDamage_Parms
	{
		float DamageAmount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Stats" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Applies damage to the owner of this component. Automatically handles health reduction and death.\n\x09 * @param DamageAmount The amount of damage to apply.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Applies damage to the owner of this component. Automatically handles health reduction and death.\n@param DamageAmount The amount of damage to apply." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DamageAmount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::NewProp_DamageAmount = { "DamageAmount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventApplyDamage_Parms, DamageAmount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::NewProp_DamageAmount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRStatsComponent, nullptr, "ApplyDamage", Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PRStatsComponent_eventApplyDamage_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::PRStatsComponent_eventApplyDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPRStatsComponent_ApplyDamage()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRStatsComponent_ApplyDamage_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRStatsComponent::execApplyDamage)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DamageAmount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyDamage(Z_Param_DamageAmount);
	P_NATIVE_END;
}
// ********** End Class UPRStatsComponent Function ApplyDamage *************************************

// ********** Begin Class UPRStatsComponent Function Die *******************************************
struct Z_Construct_UFunction_UPRStatsComponent_Die_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Handles the death of the owner. Broadcasts the OnDeathDelegate.\n\x09 */// @TODO UFUNCTION macro is needed if this will be bound to a timer or another delegate later.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles the death of the owner. Broadcasts the OnDeathDelegate.\n        // @TODO UFUNCTION macro is needed if this will be bound to a timer or another delegate later." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRStatsComponent_Die_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRStatsComponent, nullptr, "Die", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_Die_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRStatsComponent_Die_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UPRStatsComponent_Die()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRStatsComponent_Die_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRStatsComponent::execDie)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Die();
	P_NATIVE_END;
}
// ********** End Class UPRStatsComponent Function Die *********************************************

// ********** Begin Class UPRStatsComponent Function GetStatValue **********************************
struct Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics
{
	struct PRStatsComponent_eventGetStatValue_Parms
	{
		FGameplayTag StatTag;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Stats" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Gets the current value of a specified stat.\n\x09 * @param StatID The FName ID of the stat to retrieve (e.g., \"Health\").\n\x09 * @return The current float value of the stat. Returns 0 if stat is not found.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the current value of a specified stat.\n@param StatID The FName ID of the stat to retrieve (e.g., \"Health\").\n@return The current float value of the stat. Returns 0 if stat is not found." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_StatTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::NewProp_StatTag = { "StatTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventGetStatValue_Parms, StatTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(0, nullptr) }; // 133831994
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventGetStatValue_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::NewProp_StatTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRStatsComponent, nullptr, "GetStatValue", Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PRStatsComponent_eventGetStatValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::PRStatsComponent_eventGetStatValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPRStatsComponent_GetStatValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRStatsComponent_GetStatValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRStatsComponent::execGetStatValue)
{
	P_GET_STRUCT(FGameplayTag,Z_Param_StatTag);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetStatValue(Z_Param_StatTag);
	P_NATIVE_END;
}
// ********** End Class UPRStatsComponent Function GetStatValue ************************************

// ********** Begin Class UPRStatsComponent Function SetStatValue **********************************
struct Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics
{
	struct PRStatsComponent_eventSetStatValue_Parms
	{
		FGameplayTag StatTag;
		float NewValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Stats" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Internal function to set the value of a stat directly.\n\x09* @param StatID The ID of the stat to change.\n\x09* @param NewValue The new value for the stat.\n\x09*/" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Internal function to set the value of a stat directly.\n@param StatID The ID of the stat to change.\n@param NewValue The new value for the stat." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_StatTag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::NewProp_StatTag = { "StatTag", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventSetStatValue_Parms, StatTag), Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(0, nullptr) }; // 133831994
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::NewProp_NewValue = { "NewValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PRStatsComponent_eventSetStatValue_Parms, NewValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::NewProp_StatTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::NewProp_NewValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UPRStatsComponent, nullptr, "SetStatValue", Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PropPointers), sizeof(Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PRStatsComponent_eventSetStatValue_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::Function_MetaDataParams), Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::PRStatsComponent_eventSetStatValue_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UPRStatsComponent_SetStatValue()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UPRStatsComponent_SetStatValue_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UPRStatsComponent::execSetStatValue)
{
	P_GET_STRUCT(FGameplayTag,Z_Param_StatTag);
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewValue);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetStatValue(Z_Param_StatTag,Z_Param_NewValue);
	P_NATIVE_END;
}
// ********** End Class UPRStatsComponent Function SetStatValue ************************************

// ********** Begin Class UPRStatsComponent ********************************************************
void UPRStatsComponent::StaticRegisterNativesUPRStatsComponent()
{
	UClass* Class = UPRStatsComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AddXP", &UPRStatsComponent::execAddXP },
		{ "ApplyDamage", &UPRStatsComponent::execApplyDamage },
		{ "Die", &UPRStatsComponent::execDie },
		{ "GetStatValue", &UPRStatsComponent::execGetStatValue },
		{ "SetStatValue", &UPRStatsComponent::execSetStatValue },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UPRStatsComponent;
UClass* UPRStatsComponent::GetPrivateStaticClass()
{
	using TClass = UPRStatsComponent;
	if (!Z_Registration_Info_UClass_UPRStatsComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PRStatsComponent"),
			Z_Registration_Info_UClass_UPRStatsComponent.InnerSingleton,
			StaticRegisterNativesUPRStatsComponent,
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
	return Z_Registration_Info_UClass_UPRStatsComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister()
{
	return UPRStatsComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UPRStatsComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Components/PRStatsComponent.h" },
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnHealthChangedDelegate_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- DELEGATES ---\n// Other classes can bind to this delegate to be notified when health changes.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- DELEGATES ---\nOther classes can bind to this delegate to be notified when health changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnDeathDelegate_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Other classes can bind to this to be notified when the owner dies.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Other classes can bind to this to be notified when the owner dies." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnLevelUpDelegate_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Other classes can bind to this to be notified when the owner levels up.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Other classes can bind to this to be notified when the owner levels up." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnXPChangedDelegate_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Other classes can bind to this to be notified when XP changes.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Other classes can bind to this to be notified when XP changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnStatChangedDelegate_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Other classes can bind to this to be notified when any stat changes.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Other classes can bind to this to be notified when any stat changes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatsDataTable_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Config" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- PRIVATE PROPERTIES ---\n// The Data Table that defines all possible stats and their default values.\n// This should be assigned in the Blueprint derived from this component.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- PRIVATE PROPERTIES ---\nThe Data Table that defines all possible stats and their default values.\nThis should be assigned in the Blueprint derived from this component." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentStats_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Stats" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A map that holds the RUNTIME values of all stats.\n// FName is the StatID (e.g., \"Health\"), float is the current value.\n" },
#endif
		{ "ModuleRelativePath", "Public/Components/PRStatsComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A map that holds the RUNTIME values of all stats.\nFName is the StatID (e.g., \"Health\"), float is the current value." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnHealthChangedDelegate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnDeathDelegate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnLevelUpDelegate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnXPChangedDelegate;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnStatChangedDelegate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatsDataTable;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentStats_ValueProp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CurrentStats_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_CurrentStats;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UPRStatsComponent_AddXP, "AddXP" }, // 994675877
		{ &Z_Construct_UFunction_UPRStatsComponent_ApplyDamage, "ApplyDamage" }, // 1650006868
		{ &Z_Construct_UFunction_UPRStatsComponent_Die, "Die" }, // 2671818508
		{ &Z_Construct_UFunction_UPRStatsComponent_GetStatValue, "GetStatValue" }, // 1557411396
		{ &Z_Construct_UFunction_UPRStatsComponent_SetStatValue, "SetStatValue" }, // 464908945
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UPRStatsComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnHealthChangedDelegate = { "OnHealthChangedDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, OnHealthChangedDelegate), Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnHealthChangedDelegate_MetaData), NewProp_OnHealthChangedDelegate_MetaData) }; // 4118037676
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnDeathDelegate = { "OnDeathDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, OnDeathDelegate), Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnDeathDelegate_MetaData), NewProp_OnDeathDelegate_MetaData) }; // 1432351352
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnLevelUpDelegate = { "OnLevelUpDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, OnLevelUpDelegate), Z_Construct_UDelegateFunction_ProjectRumble_OnLevelUpSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnLevelUpDelegate_MetaData), NewProp_OnLevelUpDelegate_MetaData) }; // 2605569864
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnXPChangedDelegate = { "OnXPChangedDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, OnXPChangedDelegate), Z_Construct_UDelegateFunction_ProjectRumble_OnXPChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnXPChangedDelegate_MetaData), NewProp_OnXPChangedDelegate_MetaData) }; // 2487742232
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnStatChangedDelegate = { "OnStatChangedDelegate", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, OnStatChangedDelegate), Z_Construct_UDelegateFunction_ProjectRumble_OnStatChangedSignature__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnStatChangedDelegate_MetaData), NewProp_OnStatChangedDelegate_MetaData) }; // 3453717607
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_StatsDataTable = { "StatsDataTable", nullptr, (EPropertyFlags)0x0144000000010015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, StatsDataTable), Z_Construct_UClass_UDataTable_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatsDataTable_MetaData), NewProp_StatsDataTable_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats_ValueProp = { "CurrentStats", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats_Key_KeyProp = { "CurrentStats_Key", nullptr, (EPropertyFlags)0x0000000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FGameplayTag, METADATA_PARAMS(0, nullptr) }; // 133831994
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats = { "CurrentStats", nullptr, (EPropertyFlags)0x0040000000020015, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UPRStatsComponent, CurrentStats), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentStats_MetaData), NewProp_CurrentStats_MetaData) }; // 133831994
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UPRStatsComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnHealthChangedDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnDeathDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnLevelUpDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnXPChangedDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_OnStatChangedDelegate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_StatsDataTable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UPRStatsComponent_Statics::NewProp_CurrentStats,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRStatsComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UPRStatsComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UPRStatsComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UPRStatsComponent_Statics::ClassParams = {
	&UPRStatsComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UPRStatsComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UPRStatsComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UPRStatsComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UPRStatsComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UPRStatsComponent()
{
	if (!Z_Registration_Info_UClass_UPRStatsComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UPRStatsComponent.OuterSingleton, Z_Construct_UClass_UPRStatsComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UPRStatsComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UPRStatsComponent);
UPRStatsComponent::~UPRStatsComponent() {}
// ********** End Class UPRStatsComponent **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UPRStatsComponent, UPRStatsComponent::StaticClass, TEXT("UPRStatsComponent"), &Z_Registration_Info_UClass_UPRStatsComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UPRStatsComponent), 3219960109U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h__Script_ProjectRumble_3250386702(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
