// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "UI/PRHUD.h"

#ifdef PROJECTRUMBLE_PRHUD_generated_h
#error "PRHUD.generated.h already included, missing '#pragma once' in PRHUD.h"
#endif
#define PROJECTRUMBLE_PRHUD_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APRHUD *******************************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRHUD_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPRHUD(); \
	friend struct Z_Construct_UClass_APRHUD_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRHUD_NoRegister(); \
public: \
	DECLARE_CLASS2(APRHUD, AHUD, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_APRHUD_NoRegister) \
	DECLARE_SERIALIZER(APRHUD)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APRHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	APRHUD(APRHUD&&) = delete; \
	APRHUD(const APRHUD&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APRHUD); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APRHUD); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APRHUD) \
	NO_API virtual ~APRHUD();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_12_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_15_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APRHUD;

// ********** End Class APRHUD *********************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_UI_PRHUD_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
