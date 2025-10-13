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
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_PRTypes_h_18_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FStatDefinition_Statics; \
	PROJECTRUMBLE_API static class UScriptStruct* StaticStruct(); \
	typedef FTableRowBase Super;


struct FStatDefinition;
// ********** End ScriptStruct FStatDefinition *****************************************************

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

PRAGMA_ENABLE_DEPRECATION_WARNINGS
