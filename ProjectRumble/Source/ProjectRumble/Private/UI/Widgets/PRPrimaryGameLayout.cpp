// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRPrimaryGameLayout.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonActivatableWidget.h"

UCommonActivatableWidget* UPRPrimaryGameLayout::PushWidgetToLayer(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!WidgetClass) return nullptr;

	UCommonActivatableWidgetContainerBase** FoundLayer = Layers.Find(LayerTag);

	if (FoundLayer && *FoundLayer)
	{
		// AddWidget fonksiyonu eklediði widget'ý döndürür
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
	// Map'ten ilgili konteyneri bul
	UCommonActivatableWidgetContainerBase** FoundLayer = Layers.Find(LayerTag);

	if (FoundLayer && *FoundLayer)
	{
		// Konteynerin içindeki aktif widget'ý döndür
		return (*FoundLayer)->GetActiveWidget();
	}

	return nullptr;
}
