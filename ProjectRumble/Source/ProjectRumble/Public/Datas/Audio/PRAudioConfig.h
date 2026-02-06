// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRAudioConfig.generated.h"

class USoundControlBus;
class USoundControlBusMix;

UCLASS()
class PROJECTRUMBLE_API UPRAudioConfig : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundControlBusMix> DefaultMix;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TMap<FName, TObjectPtr<USoundControlBus>> AudioBuses;

};
