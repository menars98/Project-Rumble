// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PRSaveSettings.generated.h"

/**
 * Basic save object to store user preferences like audio volumes.
 */
UCLASS()
class PROJECTRUMBLE_API UPRSaveSettings : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPRSaveSettings()
	{
		// Default values
		MasterVolume = 1.0f;
		MusicVolume = 1.0f;
		SFXVolume = 1.0f;
	}

	UPROPERTY()
	float MasterVolume;

	UPROPERTY()
	float MusicVolume;

	UPROPERTY()
	float SFXVolume;
};
