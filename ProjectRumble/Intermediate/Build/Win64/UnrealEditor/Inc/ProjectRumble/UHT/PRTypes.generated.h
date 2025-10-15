// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "PRTypes.h"

#ifdef PROJECTRUMBLE_PRTypes_generated_h
#error "PRTypes.generated.h already included, missing '#pragma once' in PRTypes.h"
#endif
#define PROJECTRUMBLE_PRTypes_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FStatDefinition ***************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FStatDefinition_Statics; \
	PROJECTRUMBLE_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


struct FStatDefinition;
// ********** End ScriptStruct FStatDefinition *****************************************************

// ********** Begin ScriptStruct FUpgradeEffect ****************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h_63_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FUpgradeEffect_Statics; \
	PROJECTRUMBLE_API static class UScriptStruct* StaticStruct();


struct FUpgradeEffect;
// ********** End ScriptStruct FUpgradeEffect ******************************************************

// ********** Begin ScriptStruct FUpgradePoolEntry *************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h_86_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FUpgradePoolEntry_Statics; \
	PROJECTRUMBLE_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


struct FUpgradePoolEntry;
// ********** End ScriptStruct FUpgradePoolEntry ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h

// ********** Begin Enum EFaction ******************************************************************
#define FOREACH_ENUM_EFACTION(op) \
	op(EFaction::Player) \
	op(EFaction::Enemy) \
	op(EFaction::Neutral) 

enum class EFaction : uint8;
template<> struct TIsUEnumClass<EFaction> { enum { Value = true }; };
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EFaction>();
// ********** End Enum EFaction ********************************************************************

// ********** Begin Enum EModifierOperation ********************************************************
#define FOREACH_ENUM_EMODIFIEROPERATION(op) \
	op(EModifierOperation::Additive) \
	op(EModifierOperation::Multiplicative) 

enum class EModifierOperation : uint8;
template<> struct TIsUEnumClass<EModifierOperation> { enum { Value = true }; };
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EModifierOperation>();
// ********** End Enum EModifierOperation **********************************************************

// ********** Begin Enum EUpgradeType **************************************************************
#define FOREACH_ENUM_EUPGRADETYPE(op) \
	op(EUpgradeType::NewWeapon) \
	op(EUpgradeType::UpgradeWeapon) \
	op(EUpgradeType::NewPassiveItem) \
	op(EUpgradeType::UpgradePassiveItem) \
	op(EUpgradeType::StatBonus) 

enum class EUpgradeType : uint8;
template<> struct TIsUEnumClass<EUpgradeType> { enum { Value = true }; };
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EUpgradeType>();
// ********** End Enum EUpgradeType ****************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
