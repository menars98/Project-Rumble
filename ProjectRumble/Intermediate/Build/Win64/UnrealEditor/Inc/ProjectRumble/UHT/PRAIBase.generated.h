// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AI/PRAIBase.h"

#ifdef PROJECTRUMBLE_PRAIBase_generated_h
#error "PRAIBase.generated.h already included, missing '#pragma once' in PRAIBase.h"
#endif
#define PROJECTRUMBLE_PRAIBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APRAIBase ****************************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRAIBase_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPRAIBase(); \
	friend struct Z_Construct_UClass_APRAIBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRAIBase_NoRegister(); \
public: \
	DECLARE_CLASS2(APRAIBase, APREntityBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_APRAIBase_NoRegister) \
	DECLARE_SERIALIZER(APRAIBase)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_14_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APRAIBase(APRAIBase&&) = delete; \
	APRAIBase(const APRAIBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APRAIBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APRAIBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APRAIBase) \
	NO_API virtual ~APRAIBase();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_11_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_14_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APRAIBase;

// ********** End Class APRAIBase ******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_AI_PRAIBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
