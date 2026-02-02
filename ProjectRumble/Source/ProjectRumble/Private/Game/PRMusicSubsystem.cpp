// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PRMusicSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

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
		ActiveMusicComponent->FadeOut(FadeInDuration, 0.0f);
	}

	CurrentMusicAsset = NewMusic;

	// Spawn 2D sound for background music (no spatialization needed)
	ActiveMusicComponent = UGameplayStatics::SpawnSound2D(GetWorld(), NewMusic, 1.0f, 1.0f, 0.0f, nullptr, true);

	if (ActiveMusicComponent)
	{
		ActiveMusicComponent->FadeIn(FadeInDuration);
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

