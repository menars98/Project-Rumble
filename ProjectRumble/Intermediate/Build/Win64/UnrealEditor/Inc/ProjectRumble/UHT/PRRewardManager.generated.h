// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Managers/PRRewardManager.h"

#ifdef PROJECTRUMBLE_PRRewardManager_generated_h
#error "PRRewardManager.generated.h already included, missing '#pragma once' in PRRewardManager.h"
#endif
#define PROJECTRUMBLE_PRRewardManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UDataTable;
class UPRInventoryComponent;
class UPRUpgradeData;

// ********** Begin Class UPRRewardManager *********************************************************
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGenerateAndDraftRewards);


PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRRewardManager_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPRRewardManager(); \
	friend struct Z_Construct_UClass_UPRRewardManager_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRRewardManager_NoRegister(); \
public: \
	DECLARE_CLASS2(UPRRewardManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_UPRRewardManager_NoRegister) \
	DECLARE_SERIALIZER(UPRRewardManager)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPRRewardManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UPRRewardManager(UPRRewardManager&&) = delete; \
	UPRRewardManager(const UPRRewardManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPRRewardManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPRRewardManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPRRewardManager) \
	NO_API virtual ~UPRRewardManager();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_18_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UPRRewardManager;

// ********** End Class UPRRewardManager ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Managers_PRRewardManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
