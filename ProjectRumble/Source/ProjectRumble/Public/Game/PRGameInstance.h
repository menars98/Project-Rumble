// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PRGameInstance.generated.h"

class UDataTable;

UCLASS()
class PROJECTRUMBLE_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UDataTable> LootProfileTable;
};
