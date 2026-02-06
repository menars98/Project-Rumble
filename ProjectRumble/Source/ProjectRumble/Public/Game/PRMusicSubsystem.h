// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PRMusicSubsystem.generated.h"

class USoundControlBus;
class USoundControlBusMix;
class UPRAudioConfig;
class UPRSaveSettings;

/**
 * UPRMusicSubsystem handles global audio states, background music transitions,
 * and MetaSound parameter management.
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTRUMBLE_API UPRMusicSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Starts playing background music with a fade-in effect. */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void PlayBackgroundMusic(USoundBase* NewMusic, float FadeInDuration = 1.0f);

	/** Gradually stops the currently playing music. */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void StopBackgroundMusic(float FadeOutDuration = 1.0f);

	/** Updates a float parameter on the active MetaSound (e.g., Intensity). */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void SetMusicParameterFloat(FName ParameterName, float Value);

	/** Triggers a custom event in the active MetaSound (e.g., 'StopMusic', 'PlayDeathMusic'). */
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void TriggerMusicEvent(FName EventName);

	void InitializeConfig(UPRAudioConfig* Config);

	/**
	* Updates the volume level for a specific control bus (0.0 to 1.0).
	* @param BusName The name of the bus (Master, Music, SFX)
	* @param NewVolume Normalized volume level
	*/
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void SetVolume(FName BusName, float NewVolume);

	// Called when "Save Settings" button is clicked in UI
	UFUNCTION(BlueprintCallable, Category = "PR|Audio")
	void SaveAudioSettings(float Master, float Music, float SFX);

	// Load and Apply settings (Call this in GameInstance Init)
	void LoadAndApplySettings();

	/** Returns the currently active volume for a specific bus name. */
	UFUNCTION(BlueprintPure, Category = "PR|Audio")
	float GetVolumeLevel(FName BusName) const;

private:
	/** Reference to the currently active audio component for background music. */
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveMusicComponent;

	/** Stored pointer to avoid restarting the same track multiple times. */
	UPROPERTY()
	TObjectPtr<USoundBase> CurrentMusicAsset;

	// References to our Control Bus assets (Assign these in a Data Asset or via code)
	UPROPERTY(EditDefaultsOnly, Category = "PR|Audio")
	TMap<FName, TObjectPtr<USoundControlBus>> AudioBuses;

	UPROPERTY(EditDefaultsOnly, Category = "PR|Audio")
	TObjectPtr<USoundControlBusMix> DefaultMix;

	UPROPERTY()
	TObjectPtr<UPRAudioConfig> AudioConfig;

	const FString SettingsSlot = TEXT("AudioSettingsSlot");

	/** Cached settings to avoid redundant disk reads. */
	UPROPERTY()
	TObjectPtr<UPRSaveSettings> CachedSettings;

	void ApplyVolumesFromSettings();

	// Function name and signature must match the delegate (UWorld* only)
	void OnMapLoaded(UWorld* NewWorld);
};
