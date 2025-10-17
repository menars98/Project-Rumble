// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PRBPIPlayerHUD.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UPRBPIPlayerHUD : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTRUMBLE_API IPRBPIPlayerHUD
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// A function that can be implemented in Blueprint.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void ToggleInventory();
};
