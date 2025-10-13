// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PRTypes.h" 
#include "PREntityBase.generated.h"

class UPRStatsComponent;


UCLASS()
class PROJECTRUMBLE_API APREntityBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APREntityBase();

	// A public getter to allow other classes to easily access the Stats Component.
	UFUNCTION(BlueprintPure, Category = "PR | Components")
	UPRStatsComponent* GetStatsComponent() const { return StatsComponent; }

	// A public getter for the entity's faction.
	UFUNCTION(BlueprintPure, Category = "PR | Combat")
	EFaction GetFaction() const { return Faction; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Override the default TakeDamage function from AActor.
	// This will be the main entry point for all damage taken by this entity.
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// This function is bound to the OnHealthChangedDelegate from our StatsComponent.
	// It will be called automatically whenever health changes.
	UFUNCTION()
	virtual void OnHealthChanged(float CurrentHealth, float MaxHealth);

	// This function is bound to the OnDeathDelegate from our StatsComponent.
	// It's virtual so that child classes (like Player and AI) can have different death behaviors.
	UFUNCTION()
	virtual void OnDeath();

	// -- COMPONENTS --
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRStatsComponent> StatsComponent;

	// -- COMBAT --
	// This entity's faction. Should be set in the derived Blueprint classes.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	EFaction Faction;
};
