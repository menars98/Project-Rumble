// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PRBPIRewardScreen.generated.h"

class UPRUpgradeData;

UINTERFACE(MinimalAPI)
class UPRBPIRewardScreen : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTRUMBLE_API IPRBPIRewardScreen
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Initializes a reward screen with one or more upgrade offers.
	 * @param OfferedRewards The array of rewards to display.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI|RewardScreen")
	void InitializeScreen(const TArray<UPRUpgradeData*>& OfferedRewards);
};
