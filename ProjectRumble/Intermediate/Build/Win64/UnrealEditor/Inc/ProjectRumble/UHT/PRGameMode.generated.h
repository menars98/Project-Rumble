// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameModes/PRGameMode.h"

#ifdef PROJECTRUMBLE_PRGameMode_generated_h
#error "PRGameMode.generated.h already included, missing '#pragma once' in PRGameMode.h"
#endif
#define PROJECTRUMBLE_PRGameMode_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APRGameMode **************************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRGameMode_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPRGameMode(); \
	friend struct Z_Construct_UClass_APRGameMode_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRGameMode_NoRegister(); \
public: \
	DECLARE_CLASS2(APRGameMode, AGameMode, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_APRGameMode_NoRegister) \
	DECLARE_SERIALIZER(APRGameMode)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APRGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	APRGameMode(APRGameMode&&) = delete; \
	APRGameMode(const APRGameMode&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APRGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APRGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APRGameMode) \
	NO_API virtual ~APRGameMode();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_12_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APRGameMode;

// ********** End Class APRGameMode ****************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_GameModes_PRGameMode_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
