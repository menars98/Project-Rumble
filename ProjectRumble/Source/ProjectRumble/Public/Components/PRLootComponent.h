// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h" 
#include "PRLootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRUMBLE_API UPRLootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPRLootComponent();

	/**
	 * Main function to generate and drop loot.
	 * Reads the owner's profile tag and finds the corresponding loot in the global loot table.
	 */
	UFUNCTION(BlueprintCallable, Category = "Loot")
	void DropLoot();
protected:
	virtual void BeginPlay() override;

	// The Gameplay Tag that identifies which loot profile to use for this component's owner.
	// e.g., "Enemy.Type.Goblin", "Destructible.Type.Vase"
	// This should be set on the component in the owning actor's Blueprint.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
	FGameplayTag LootProfileTag;

		
};
