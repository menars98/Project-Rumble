// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PRActivatableWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRUMBLE_API UPRActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:

	//@TODO: In later we can add sound effects, starting animations etc.
	// 
	// Sound to play when this widget is activated.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<USoundBase> ActivationSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bAutoPauseGame = false;

protected:
	// Override the NativeOnActivated function to play the sound when the widget is activated.
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
};
