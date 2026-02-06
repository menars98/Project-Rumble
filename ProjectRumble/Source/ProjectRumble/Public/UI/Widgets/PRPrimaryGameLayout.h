// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "GameplayTagContainer.h"
#include "PRPrimaryGameLayout.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API UPRPrimaryGameLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:
    // Tags defining layers (Game, Menu, Modal)
    // We will use this function on the C++ side to push widgets to the correct location.
    UFUNCTION(BlueprintCallable, Category = "Layer")
    UCommonActivatableWidget* PushWidgetToLayer(FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass);

   
    // Registers a widget stack (Layer) to a specific tag.
    UFUNCTION(BlueprintCallable, Category = "Layer")
    void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);

    /**
    * Returns the currently active widget in the specified layer.
    * Used by APRHUD to access the HUD widget.
    */
    UFUNCTION(BlueprintCallable, Category = "Layer")
    UCommonActivatableWidget* GetActiveWidgetInLayer(FGameplayTag LayerTag);

    /** Static helper to get the primary layout from anywhere. */
    UFUNCTION(BlueprintPure, Category = "PR|UI", meta = (WorldContext = "WorldContextObject"))
    static UPRPrimaryGameLayout* GetPrimaryGameLayout(const UObject* WorldContextObject);
protected:
    // We will connect the “Stacks” we will create in Blueprint here.
    // E.g.: GameLayerStack, MenuLayerStack...
    // Maps a GameplayTag (e.g., UI.Layer.Menu) to the actual Widget Container
    UPROPERTY(Transient)
    TMap<FGameplayTag, UCommonActivatableWidgetContainerBase*> Layers;
};
