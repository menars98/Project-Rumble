// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PRDamageableInterface.generated.h"

class UPRStatsComponent;


UINTERFACE(MinimalAPI)
class UPRDamageableInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECTRUMBLE_API IPRDamageableInterface
{
	GENERATED_BODY()

public:
	/**
	 *  Every actor implementing this function must return its own StatsComponent.
     * This way, we won't have to use “FindComponentByClass” to search for it.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UPRStatsComponent* GetStatComponent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void ReactToDamage(float DamageAmount);


};
