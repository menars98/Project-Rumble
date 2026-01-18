// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRActivatableWidget.h"
#include "Kismet/GameplayStatics.h"

void UPRActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (ActivationSound)
	{
		UGameplayStatics::PlaySound2D(this, ActivationSound);
	}
	if (bAutoPauseGame)
	{
		UGameplayStatics::SetGamePaused(this, true);
	}
	// Log (Debug)
	// UE_LOG(LogTemp, Log, TEXT("UI: %s Activated"), *GetName());
}

void UPRActivatableWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	// --- UNPAUSE LOGIC ---
	// Only unpause if this widget paused the game.
	if (bAutoPauseGame)
	{
		UGameplayStatics::SetGamePaused(this, false);
	}
}
