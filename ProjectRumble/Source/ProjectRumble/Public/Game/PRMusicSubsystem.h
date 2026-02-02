// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PRMusicSubsystem.generated.h"

/**
 * UPRMusicSubsystem handles global audio states, background music transitions,
 * and MetaSound parameter management.
 */
UCLASS()
class PROJECTRUMBLE_API UPRMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/** Starts playing background music with a fade-in effect. */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void PlayBackgroundMusic(USoundBase* NewMusic, float FadeInDuration = 1.0f);

	/** Gradually stops the currently playing music. */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void StopBackgroundMusic(float FadeOutDuration = 1.0f);

	/** Updates a float parameter on the active MetaSound (e.g., Intensity). */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void SetMusicParameterFloat(FName ParameterName, float Value);

private:
	/** Reference to the currently active audio component for background music. */
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveMusicComponent;

	/** Stored pointer to avoid restarting the same track multiple times. */
	UPROPERTY()
	TObjectPtr<USoundBase> CurrentMusicAsset;
};
