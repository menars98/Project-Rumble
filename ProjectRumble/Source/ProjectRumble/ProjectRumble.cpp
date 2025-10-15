// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectRumble.h"
#include "Modules/ModuleManager.h"
#include "PRGameplayTags.h"

class FProjectRumbleModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{

	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ProjectRumble, "ProjectRumble" );
