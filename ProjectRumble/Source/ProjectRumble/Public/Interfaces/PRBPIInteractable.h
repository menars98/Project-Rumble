// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PRBPIInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPRBPIInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTRUMBLE_API IPRBPIInteractable
{
	GENERATED_BODY()

public:

	// Function called when the player interacts with this object.
	// Must be implemented in the Blueprint that uses this interface.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void Interact(APawn* InstigatorPawn);
};
