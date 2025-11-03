// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PRBaseWidget.generated.h"

class USoundBase;

UCLASS()
class PROJECTRUMBLE_API UPRBaseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** Sound to play when this widget appears/is initialized (e.g., Level Up screen fanfare). */
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> InitializeSound;

protected:
	// Instead of using Native Tick to capture the time the widget was created,
	// we use NativeConstruct.
	virtual void NativeConstruct() override;

};
