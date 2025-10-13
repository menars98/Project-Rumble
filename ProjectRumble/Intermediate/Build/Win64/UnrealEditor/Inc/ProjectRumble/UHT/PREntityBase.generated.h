// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Characters/PREntityBase.h"

#ifdef PROJECTRUMBLE_PREntityBase_generated_h
#error "PREntityBase.generated.h already included, missing '#pragma once' in PREntityBase.h"
#endif
#define PROJECTRUMBLE_PREntityBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UPRStatsComponent;
enum class EFaction : uint8;

// ********** Begin Class APREntityBase ************************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnDeath); \
	DECLARE_FUNCTION(execOnHealthChanged); \
	DECLARE_FUNCTION(execGetFaction); \
	DECLARE_FUNCTION(execGetStatsComponent);


PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPREntityBase(); \
	friend struct Z_Construct_UClass_APREntityBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_APREntityBase_NoRegister(); \
public: \
	DECLARE_CLASS2(APREntityBase, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_APREntityBase_NoRegister) \
	DECLARE_SERIALIZER(APREntityBase)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APREntityBase(APREntityBase&&) = delete; \
	APREntityBase(const APREntityBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APREntityBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APREntityBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APREntityBase) \
	NO_API virtual ~APREntityBase();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_13_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APREntityBase;

// ********** End Class APREntityBase **************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PREntityBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
