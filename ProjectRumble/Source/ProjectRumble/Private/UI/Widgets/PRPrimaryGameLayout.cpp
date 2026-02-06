// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRPrimaryGameLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonActivatableWidget.h"
#include <UI/PRHUD.h>

UCommonActivatableWidget* UPRPrimaryGameLayout::PushWidgetToLayer(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!WidgetClass) return nullptr;

	UCommonActivatableWidgetContainerBase** FoundLayer = Layers.Find(LayerTag);

	if (FoundLayer && *FoundLayer)
	{
		// Add the widget to the found layer container and return it
		return (*FoundLayer)->AddWidget(WidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find Layer for Tag: %s. Make sure to register it in BP_PrimaryLayout!"), *LayerTag.ToString());
	}
	return nullptr;
}

void UPRPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!LayerWidget) return;

	Layers.Add(LayerTag, LayerWidget);

	// Log to confirm registration
	// UE_LOG(LogTemp, Log, TEXT("Registered UI Layer: %s"), *LayerTag.ToString());
}

UCommonActivatableWidget* UPRPrimaryGameLayout::GetActiveWidgetInLayer(FGameplayTag LayerTag)
{
	// Find the layer container for the given tag
	UCommonActivatableWidgetContainerBase** FoundLayer = Layers.Find(LayerTag);

	if (FoundLayer && *FoundLayer)
	{
		// Return the active widget in that layer
		return (*FoundLayer)->GetActiveWidget();
	}

	return nullptr;
}

UPRPrimaryGameLayout* UPRPrimaryGameLayout::GetPrimaryGameLayout(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;

	APlayerController* PC = GEngine->GetFirstLocalPlayerController(WorldContextObject->GetWorld());
	if (PC && PC->GetHUD())
	{
		// Assuming your HUD class has a getter for RootLayout
		if (APRHUD* PRHUD = Cast<APRHUD>(PC->GetHUD()))
		{
			return PRHUD->GetMainLayout();
		}
	}
	return nullptr;
}
