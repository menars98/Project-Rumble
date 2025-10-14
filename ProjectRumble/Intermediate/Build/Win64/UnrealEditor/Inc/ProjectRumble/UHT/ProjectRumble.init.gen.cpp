// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProjectRumble_init() {}
	PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature();
	PROJECTRUMBLE_API UFunction* Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_ProjectRumble;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_ProjectRumble()
	{
		if (!Z_Registration_Info_UPackage__Script_ProjectRumble.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_ProjectRumble_OnDeathSignature__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_ProjectRumble_OnHealthChangedSignature__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/ProjectRumble",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x55BC3497,
				0x4BAD519C,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_ProjectRumble.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_ProjectRumble.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_ProjectRumble(Z_Construct_UPackage__Script_ProjectRumble, TEXT("/Script/ProjectRumble"), Z_Registration_Info_UPackage__Script_ProjectRumble, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x55BC3497, 0x4BAD519C));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
