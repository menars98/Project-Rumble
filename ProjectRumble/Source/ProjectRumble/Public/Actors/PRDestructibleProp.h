// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Interfaces/PRDamageableInterface.h"
#include "PRDestructibleProp.generated.h"

class UPRStatsComponent;
class UPRLootComponent;
class UStaticMeshComponent;

UCLASS()
class PROJECTRUMBLE_API APRDestructibleProp : public AActor, public IPRDamageableInterface
{

	GENERATED_BODY()

public:
	APRDestructibleProp();

protected:
	virtual void BeginPlay() override;

	// --- COMPONENTS ---
	// Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	// Health & Knockback
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRStatsComponent> StatsComp;

	// Loot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRLootComponent> LootComp;

	// --- LOGIC ---
	// Tag ID
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FGameplayTag PropID;

	UFUNCTION()
	void OnPropDestroyed();

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual UPRStatsComponent* GetStatComponent_Implementation() const override { return StatsComp; }

	virtual void ReactToDamage_Implementation(float DamageAmount) override;

};
