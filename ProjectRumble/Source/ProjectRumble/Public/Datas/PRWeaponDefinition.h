// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Datas/PRItemDefinition.h"
#include "PRTypes.h"
#include "PRWeaponDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTRUMBLE_API UPRWeaponDefinition : public UPRItemDefinition
{
	GENERATED_BODY()
	
public:

	// Weapon Stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Data")
	FWeaponStats WeaponStats;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
