// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Datas/PRUpgradeData.h"

#ifdef PROJECTRUMBLE_PRUpgradeData_generated_h
#error "PRUpgradeData.generated.h already included, missing '#pragma once' in PRUpgradeData.h"
#endif
#define PROJECTRUMBLE_PRUpgradeData_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UPRUpgradeData ***********************************************************
PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister();

#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_24_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPRUpgradeData(); \
	friend struct Z_Construct_UClass_UPRUpgradeData_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend PROJECTRUMBLE_API UClass* Z_Construct_UClass_UPRUpgradeData_NoRegister(); \
public: \
	DECLARE_CLASS2(UPRUpgradeData, UDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ProjectRumble"), Z_Construct_UClass_UPRUpgradeData_NoRegister) \
	DECLARE_SERIALIZER(UPRUpgradeData)


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_24_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPRUpgradeData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UPRUpgradeData(UPRUpgradeData&&) = delete; \
	UPRUpgradeData(const UPRUpgradeData&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPRUpgradeData); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPRUpgradeData); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPRUpgradeData) \
	NO_API virtual ~UPRUpgradeData();


#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_21_PROLOG
#define FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_24_INCLASS_NO_PURE_DECLS \
	FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UPRUpgradeData;

// ********** End Class UPRUpgradeData *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_muham_Documents_GitHub_Project_Rumble_ProjectRumble_Source_ProjectRumble_Public_Datas_PRUpgradeData_h

// ********** Begin Enum EUpgradeRarity ************************************************************
#define FOREACH_ENUM_EUPGRADERARITY(op) \
	op(EUpgradeRarity::Common) \
	op(EUpgradeRarity::Uncommon) \
	op(EUpgradeRarity::Rare) \
	op(EUpgradeRarity::Epic) \
	op(EUpgradeRarity::Legendary) 

enum class EUpgradeRarity : uint8;
template<> struct TIsUEnumClass<EUpgradeRarity> { enum { Value = true }; };
template<> PROJECTRUMBLE_API UEnum* StaticEnum<EUpgradeRarity>();
// ********** End Enum EUpgradeRarity **************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
