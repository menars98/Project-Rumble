// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRItemDefinition.h"
#include "PRTypes.h"
#include "PRPassiveItemDefinition.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTRUMBLE_API UPRPassiveItemDefinition : public UPRItemDefinition
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Passive Data")
	FPassiveAbilityStats AbilityStats;
};
