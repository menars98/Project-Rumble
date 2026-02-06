// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PRMusicSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AudioModulationStatics.h"
#include "SoundControlBus.h"
#include "Datas/Audio/PRAudioConfig.h"
#include "Save/PRSaveSettings.h"

void UPRMusicSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UPRMusicSubsystem::OnMapLoaded);
}

void UPRMusicSubsystem::OnMapLoaded(UWorld* NewWorld)
{
	if (!NewWorld) return;

	// When a new world (Lobby or Game) is ready, force-load settings and apply them
	// This ensures ActivateBusMix is called in the context of the NEW world.
	LoadAndApplySettings();

	UE_LOG(LogTemp, Log, TEXT("Audio Subsystem: Map %s loaded. Audio settings applied."), *NewWorld->GetName());
}

void UPRMusicSubsystem::PlayBackgroundMusic(USoundBase* NewMusic, float FadeInDuration)
{
	// Avoid restarting if the same music is already playing
	if (!NewMusic || CurrentMusicAsset == NewMusic)
	{
		return;
	}

	// Fade out existing music if applicable
	if (ActiveMusicComponent && ActiveMusicComponent->IsPlaying())
	{
		// Ensure the sound doesn't auto-destroy when one track ends inside MetaSound
		ActiveMusicComponent->bAutoDestroy = false;
		ActiveMusicComponent->FadeOut(FadeInDuration, 0.0f);
	}

	CurrentMusicAsset = NewMusic;

	// Spawn 2D sound for background music (no spatialization needed)
	ActiveMusicComponent = UGameplayStatics::SpawnSound2D(GetWorld(), NewMusic, 1.0f, 1.0f, 0.0f, nullptr, true);

	if (ActiveMusicComponent)
	{
		ActiveMusicComponent->FadeIn(FadeInDuration);

		ApplyVolumesFromSettings();
	}
}

void UPRMusicSubsystem::StopBackgroundMusic(float FadeOutDuration)
{
	if (ActiveMusicComponent && ActiveMusicComponent->IsPlaying())
	{
		ActiveMusicComponent->FadeOut(FadeOutDuration, 0.0f);
		CurrentMusicAsset = nullptr;
	}
}

void UPRMusicSubsystem::SetMusicParameterFloat(FName ParameterName, float Value)
{
	if (ActiveMusicComponent)
	{
		// SetParameter is used for MetaSounds to update dynamic logic
		ActiveMusicComponent->SetFloatParameter(ParameterName, Value);
	}
}

void UPRMusicSubsystem::TriggerMusicEvent(FName EventName)
{
	if (ActiveMusicComponent)
	{
		ActiveMusicComponent->SetTriggerParameter(EventName);
	}
}

void UPRMusicSubsystem::InitializeConfig(UPRAudioConfig* Config)
{
	if (Config)
	{
		AudioConfig = Config;
		
		LoadAndApplySettings();

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPRMusicSubsystem::ApplyVolumesFromSettings, 0.2f, false);
	}
}

void UPRMusicSubsystem::SetVolume(FName BusName, float NewVolume)
{
	if (!AudioConfig || !AudioConfig->DefaultMix || !AudioConfig->AudioBuses.Contains(BusName)) return;
	
	UAudioModulationStatics::ActivateBusMix(GetWorld(), AudioConfig->DefaultMix);

	// 1. Create a "Stage" for the mix
	FSoundControlBusMixStage MixStage;
	MixStage.Bus = AudioConfig->AudioBuses[BusName];
	MixStage.Value.TargetValue = NewVolume;
	MixStage.Value.AttackTime = 0.01f;  
	MixStage.Value.ReleaseTime = 0.01f;

	// 2. Put it into an array (The API expects an array)
	TArray<FSoundControlBusMixStage> Stages;
	Stages.Add(MixStage);

	// 3. Update the Mix Asset dynamically
	// This tells Unreal: "In our DefaultMix, update the specific Bus with this new value"
	UAudioModulationStatics::UpdateMix(GetWorld(), AudioConfig->DefaultMix, Stages);
	
}

void UPRMusicSubsystem::SaveAudioSettings(float Master, float Music, float SFX)
{
	if (!CachedSettings)
	{
		CachedSettings = Cast<UPRSaveSettings>(UGameplayStatics::CreateSaveGameObject(UPRSaveSettings::StaticClass()));
	}

	if (CachedSettings)
	{
		// 2. Update the in-memory values
		CachedSettings->MasterVolume = Master;
		CachedSettings->MusicVolume = Music;
		CachedSettings->SFXVolume = SFX;

		// 3. Persist the data to disk
		UGameplayStatics::SaveGameToSlot(CachedSettings, SettingsSlot, 0);

		// 4. Apply changes to the audio system instantly
		ApplyVolumesFromSettings();

		UE_LOG(LogTemp, Warning, TEXT("SAVED: M:%.2f Mus:%.2f SFX:%.2f"), Master, Music, SFX);
		UE_LOG(LogTemp, Log, TEXT("Audio Settings Saved and Applied."));
	}
}

void UPRMusicSubsystem::LoadAndApplySettings()
{
	if (UGameplayStatics::DoesSaveGameExist(SettingsSlot, 0))
	{
		CachedSettings = Cast<UPRSaveSettings>(UGameplayStatics::LoadGameFromSlot(SettingsSlot, 0));
		UE_LOG(LogTemp, Warning, TEXT("Audio Settings LOADED from disk. Master: %.2f"), CachedSettings->MasterVolume);
	}

	// If no save exists, create a default one so CachedSettings is never null
	if (!CachedSettings)
	{
		CachedSettings = Cast<UPRSaveSettings>(UGameplayStatics::CreateSaveGameObject(UPRSaveSettings::StaticClass()));
		// Save the default settings so the file actually exists on disk
		UGameplayStatics::SaveGameToSlot(CachedSettings, SettingsSlot, 0);
		UE_LOG(LogTemp, Warning, TEXT("AudioSubsystem: No save file found. Created default settings on disk."));
	}

	if (CachedSettings)
	{
		ApplyVolumesFromSettings();
	}
}

float UPRMusicSubsystem::GetVolumeLevel(FName BusName) const
{
	if (!CachedSettings) return 1.0f; // Default fallback

	if (BusName == FName("Master")) return CachedSettings->MasterVolume;
	if (BusName == FName("Music"))  return CachedSettings->MusicVolume;
	if (BusName == FName("SFX"))    return CachedSettings->SFXVolume;

	return 1.0f;
}

void UPRMusicSubsystem::ApplyVolumesFromSettings()
{
	UWorld* World = (ActiveMusicComponent) ? ActiveMusicComponent->GetWorld() : GetGameInstance()->GetWorld();
	if (!World || !AudioConfig || !AudioConfig->DefaultMix || !CachedSettings) return;

	
	UAudioModulationStatics::ActivateBusMix(World, AudioConfig->DefaultMix);

	// 2. Gather all stages for the buses we want to update
	TArray<FSoundControlBusMixStage> Stages;

	auto SetBusValue = [&](FName BusName, float Volume)
		{
			if (AudioConfig->AudioBuses.Contains(BusName))
			{
				FSoundControlBusMixStage Stage;
				Stage.Bus = AudioConfig->AudioBuses[BusName];
				Stage.Value.TargetValue = Volume;
				Stage.Value.AttackTime = 0.01f;
				Stage.Value.ReleaseTime = 0.01f;

				TArray<FSoundControlBusMixStage> Stages;
				Stages.Add(Stage);

				// "Filter" parametrelerini boþ býrakarak direkt bu bus'a odaklanýyoruz
				UAudioModulationStatics::UpdateMix(World, AudioConfig->DefaultMix, Stages);
			}
		};

	SetBusValue(FName("Master"), CachedSettings->MasterVolume);
	SetBusValue(FName("Music"), CachedSettings->MusicVolume);
	SetBusValue(FName("SFX"), CachedSettings->SFXVolume);

	// 3. Apply all the stages to the mix at once for efficiency
	UAudioModulationStatics::UpdateMix(World, AudioConfig->DefaultMix, Stages);

	UE_LOG(LogTemp, Log, TEXT("Audio Subsystem: Batch update applied successfully."));
}
