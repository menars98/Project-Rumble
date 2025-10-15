// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PREntityBase.h"
#include "PRAIBase.generated.h"

class UPRStatsComponent;

UCLASS()
class PROJECTRUMBLE_API APRAIBase : public APREntityBase
{
	GENERATED_BODY()
	
public:
	APRAIBase();

	

protected:
	// -- COMPONENTS --
	// The AI has its own StatsComponent directly on itself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRStatsComponent> StatsComponent_AI; // Renamed to avoid confusion with the inherited pointer name.

	// The amount of XP this AI drops when it dies.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	float XPToAward = 25.0f;

	// -- OVERRIDDEN FUNCTIONS --
	// We override GetStatsComponent to return our own component.
	virtual UPRStatsComponent* GetStatsComponent() const override;

	// We override OnDeath to add our "drop XP" logic.
	virtual void OnDeath() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
};

