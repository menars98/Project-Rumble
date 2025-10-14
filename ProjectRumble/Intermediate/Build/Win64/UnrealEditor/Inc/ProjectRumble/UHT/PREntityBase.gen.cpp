// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Characters/PREntityBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodePREntityBase() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase_NoRegister();
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister();
PROJECTRUMBLE_API UEnum* Z_Construct_UEnum_ProjectRumble_EFaction();
UPackage* Z_Construct_UPackage__Script_ProjectRumble();
// ********** End Cross Module References **********************************************************

// ********** Begin Class APREntityBase Function GetFaction ****************************************
struct Z_Construct_UFunction_APREntityBase_GetFaction_Statics
{
	struct PREntityBase_eventGetFaction_Parms
	{
		EFaction ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A public getter for the entity's faction.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A public getter for the entity's faction." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_APREntityBase_GetFaction_Statics::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_APREntityBase_GetFaction_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PREntityBase_eventGetFaction_Parms, ReturnValue), Z_Construct_UEnum_ProjectRumble_EFaction, METADATA_PARAMS(0, nullptr) }; // 3868884884
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APREntityBase_GetFaction_Statics::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APREntityBase_GetFaction_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APREntityBase_GetFaction_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APREntityBase, nullptr, "GetFaction", Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PropPointers), sizeof(Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PREntityBase_eventGetFaction_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetFaction_Statics::Function_MetaDataParams), Z_Construct_UFunction_APREntityBase_GetFaction_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APREntityBase_GetFaction_Statics::PREntityBase_eventGetFaction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APREntityBase_GetFaction()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APREntityBase_GetFaction_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APREntityBase::execGetFaction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(EFaction*)Z_Param__Result=P_THIS->GetFaction();
	P_NATIVE_END;
}
// ********** End Class APREntityBase Function GetFaction ******************************************

// ********** Begin Class APREntityBase Function GetStatsComponent *********************************
struct Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics
{
	struct PREntityBase_eventGetStatsComponent_Parms
	{
		UPRStatsComponent* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "PR | Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// A public getter to allow other classes to easily access the Stats Component.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A public getter to allow other classes to easily access the Stats Component." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "EditInline", "true" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000080588, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PREntityBase_eventGetStatsComponent_Parms, ReturnValue), Z_Construct_UClass_UPRStatsComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APREntityBase, nullptr, "GetStatsComponent", Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PropPointers), sizeof(Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PREntityBase_eventGetStatsComponent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::Function_MetaDataParams), Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::PREntityBase_eventGetStatsComponent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APREntityBase_GetStatsComponent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APREntityBase_GetStatsComponent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APREntityBase::execGetStatsComponent)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UPRStatsComponent**)Z_Param__Result=P_THIS->GetStatsComponent();
	P_NATIVE_END;
}
// ********** End Class APREntityBase Function GetStatsComponent ***********************************

// ********** Begin Class APREntityBase Function OnDeath *******************************************
struct Z_Construct_UFunction_APREntityBase_OnDeath_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This function is bound to the OnDeathDelegate from our StatsComponent.\n// It's virtual so that child classes (like Player and AI) can have different death behaviors.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This function is bound to the OnDeathDelegate from our StatsComponent.\nIt's virtual so that child classes (like Player and AI) can have different death behaviors." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APREntityBase_OnDeath_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APREntityBase, nullptr, "OnDeath", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_OnDeath_Statics::Function_MetaDataParams), Z_Construct_UFunction_APREntityBase_OnDeath_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_APREntityBase_OnDeath()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APREntityBase_OnDeath_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APREntityBase::execOnDeath)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnDeath();
	P_NATIVE_END;
}
// ********** End Class APREntityBase Function OnDeath *********************************************

// ********** Begin Class APREntityBase Function OnHealthChanged ***********************************
struct Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics
{
	struct PREntityBase_eventOnHealthChanged_Parms
	{
		float CurrentHealth;
		float MaxHealth;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// This function is bound to the OnHealthChangedDelegate from our StatsComponent.\n// It will be called automatically whenever health changes.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "This function is bound to the OnHealthChangedDelegate from our StatsComponent.\nIt will be called automatically whenever health changes." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHealth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHealth;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::NewProp_CurrentHealth = { "CurrentHealth", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PREntityBase_eventOnHealthChanged_Parms, CurrentHealth), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::NewProp_MaxHealth = { "MaxHealth", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(PREntityBase_eventOnHealthChanged_Parms, MaxHealth), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::NewProp_CurrentHealth,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::NewProp_MaxHealth,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_APREntityBase, nullptr, "OnHealthChanged", Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PropPointers), sizeof(Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PREntityBase_eventOnHealthChanged_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::Function_MetaDataParams), Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::PREntityBase_eventOnHealthChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APREntityBase_OnHealthChanged()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_APREntityBase_OnHealthChanged_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(APREntityBase::execOnHealthChanged)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_CurrentHealth);
	P_GET_PROPERTY(FFloatProperty,Z_Param_MaxHealth);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnHealthChanged(Z_Param_CurrentHealth,Z_Param_MaxHealth);
	P_NATIVE_END;
}
// ********** End Class APREntityBase Function OnHealthChanged *************************************

// ********** Begin Class APREntityBase ************************************************************
void APREntityBase::StaticRegisterNativesAPREntityBase()
{
	UClass* Class = APREntityBase::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetFaction", &APREntityBase::execGetFaction },
		{ "GetStatsComponent", &APREntityBase::execGetStatsComponent },
		{ "OnDeath", &APREntityBase::execOnDeath },
		{ "OnHealthChanged", &APREntityBase::execOnHealthChanged },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APREntityBase;
UClass* APREntityBase::GetPrivateStaticClass()
{
	using TClass = APREntityBase;
	if (!Z_Registration_Info_UClass_APREntityBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("PREntityBase"),
			Z_Registration_Info_UClass_APREntityBase.InnerSingleton,
			StaticRegisterNativesAPREntityBase,
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
	return Z_Registration_Info_UClass_APREntityBase.InnerSingleton;
}
UClass* Z_Construct_UClass_APREntityBase_NoRegister()
{
	return APREntityBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_APREntityBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Characters/PREntityBase.h" },
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Faction_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// -- COMBAT --\n// This entity's faction. Should be set in the derived Blueprint classes.\n" },
#endif
		{ "ModuleRelativePath", "Public/Characters/PREntityBase.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "-- COMBAT --\nThis entity's faction. Should be set in the derived Blueprint classes." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Faction_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Faction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APREntityBase_GetFaction, "GetFaction" }, // 3914408080
		{ &Z_Construct_UFunction_APREntityBase_GetStatsComponent, "GetStatsComponent" }, // 2943575766
		{ &Z_Construct_UFunction_APREntityBase_OnDeath, "OnDeath" }, // 3245300973
		{ &Z_Construct_UFunction_APREntityBase_OnHealthChanged, "OnHealthChanged" }, // 3700949402
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APREntityBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_APREntityBase_Statics::NewProp_Faction_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_APREntityBase_Statics::NewProp_Faction = { "Faction", nullptr, (EPropertyFlags)0x0020080000010015, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(APREntityBase, Faction), Z_Construct_UEnum_ProjectRumble_EFaction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Faction_MetaData), NewProp_Faction_MetaData) }; // 3868884884
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_APREntityBase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APREntityBase_Statics::NewProp_Faction_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_APREntityBase_Statics::NewProp_Faction,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APREntityBase_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_APREntityBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_ProjectRumble,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_APREntityBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_APREntityBase_Statics::ClassParams = {
	&APREntityBase::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_APREntityBase_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_APREntityBase_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_APREntityBase_Statics::Class_MetaDataParams), Z_Construct_UClass_APREntityBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_APREntityBase()
{
	if (!Z_Registration_Info_UClass_APREntityBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APREntityBase.OuterSingleton, Z_Construct_UClass_APREntityBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_APREntityBase.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(APREntityBase);
APREntityBase::~APREntityBase() {}
// ********** End Class APREntityBase **************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h__Script_ProjectRumble_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APREntityBase, APREntityBase::StaticClass, TEXT("APREntityBase"), &Z_Registration_Info_UClass_APREntityBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APREntityBase), 4271531848U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h__Script_ProjectRumble_1017551055(TEXT("/Script/ProjectRumble"),
	Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h__Script_ProjectRumble_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h__Script_ProjectRumble_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
