// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/PRPickupBase.h"
#include "PRGoldPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API APRGoldPickup : public APRPickupBase
{
	GENERATED_BODY()
	
protected:
	virtual void OnCollected_Implementation() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
