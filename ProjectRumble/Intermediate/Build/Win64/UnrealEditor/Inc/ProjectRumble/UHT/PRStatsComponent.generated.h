// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Components/PRStatsComponent.h"

#ifdef PROJECTRUMBLE_PRStatsComponent_generated_h
#error "PRStatsComponent.generated.h already included, missing '#pragma once' in PRStatsComponent.h"
#endif
#define PROJECTRUMBLE_PRStatsComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FOnHealthChangedSignature *********************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_13_DELEGATE \
PROJECTRUMBLE_API void FOnHealthChangedSignature_DelegateWrapper(const FMulticastScriptDelegate& OnHealthChangedSignature, float CurrentHealth, float MaxHealth);


// ********** End Delegate FOnHealthChangedSignature ***********************************************

// ********** Begin Delegate FOnDeathSignature *****************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_16_DELEGATE \
PROJECTRUMBLE_API void FOnDeathSignature_DelegateWrapper(const FMulticastScriptDelegate& OnDeathSignature);


// ********** End Delegate FOnDeathSignature *******************************************************

// ********** Begin Class UPRStatsComponent ********************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDie); \
	DECLARE_FUNCTION(execApplyDamage); \
	DECLARE_FUNCTION(execGetStatValue);


PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPRStatsComponent(); \
	friend struct Z_Construct_UClass_UPRStatsComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRStatsComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UPRStatsComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_UPRStatsComponent_NoRegister) \
	DECLARE_SERIALIZER(UPRStatsComponent)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UPRStatsComponent(UPRStatsComponent&&) = delete; \
	UPRStatsComponent(const UPRStatsComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPRStatsComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPRStatsComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UPRStatsComponent) \
	NO_API virtual ~UPRStatsComponent();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_19_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UPRStatsComponent;

// ********** End Class UPRStatsComponent **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Components_PRStatsComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
