// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Characters/PRCharacterBase.h"

#ifdef PROJECTRUMBLE_PRCharacterBase_generated_h
#error "PRCharacterBase.generated.h already included, missing '#pragma once' in PRCharacterBase.h"
#endif
#define PROJECTRUMBLE_PRCharacterBase_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APRCharacterBase *********************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRCharacterBase_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPRCharacterBase(); \
	friend struct Z_Construct_UClass_APRCharacterBase_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_APRCharacterBase_NoRegister(); \
public: \
	DECLARE_CLASS2(APRCharacterBase, APREntityBase, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_APRCharacterBase_NoRegister) \
	DECLARE_SERIALIZER(APRCharacterBase)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APRCharacterBase(APRCharacterBase&&) = delete; \
	APRCharacterBase(const APRCharacterBase&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APRCharacterBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APRCharacterBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APRCharacterBase) \
	NO_API virtual ~APRCharacterBase();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_19_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APRCharacterBase;

// ********** End Class APRCharacterBase ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Characters_PRCharacterBase_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
