// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PREntityBase.h"
#include "PRAIBase.generated.h"

class UPRStatsComponent;
class APRCharacterBase;

UCLASS()
class PROJECTRUMBLE_API APRAIBase : public APREntityBase
{
	GENERATED_BODY()
	
public:
	APRAIBase();

	
	/** Returns the Gameplay Tags associated with this AI. */
	UFUNCTION(BlueprintPure, Category = "AI")
	const FGameplayTagContainer& GetAITags() const { return AITags; }

protected:
	// -- COMPONENTS --
	// The AI has its own StatsComponent directly on itself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<UPRStatsComponent> StatsComponent_AI; // Renamed to avoid confusion with the inherited pointer name.

	// The amount of XP this AI drops when it dies.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Loot")
	float XPToAward = 25.0f;

	// -- COMBAT --
	// The damage this AI deals on contact.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactDamage = 5.0f; 

	// How often (in seconds) to apply contact damage while overlapping.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float DamageInterval = 2.0f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Loot")
	float KnockbackStrengthToPlayer = 500.0f;

	// The player we are currently in contact with.
	UPROPERTY()
	TObjectPtr<APRCharacterBase> ContactTarget;

	// A pointer to the dynamic material instance for hit flash effects.
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	// The timer handle to manage the duration of the flash effect.
	FTimerHandle FlashTimerHandle;

	// The timer handle for applying contact damage.
	FTimerHandle ContactDamageTimerHandle;

	// Flag to check if we are currently able to apply contact damage.
	bool bCanApplyContactDamage = true;

	// -- AI TAGS --
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | AI")
	FGameplayTagContainer AITags;

	// Function to start the flash effect.
	void PlayHitFlash();

	// Function to end the flash effect.
	void StopHitFlash();

	// -- OVERRIDDEN FUNCTIONS --
	// We override GetStatsComponent to return our own component.
	virtual UPRStatsComponent* GetStatsComponent() const override;

	// We override OnDeath to add our "drop XP" logic.
	virtual void OnDeath() override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// -- ONHIT & OVERLAP EVENTS --

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Function to apply contact damage to the target player.
	void ApplyContactDamage(APRCharacterBase* TargetPlayer);
	
	// Function called by the timer to re-enable contact damage.
	UFUNCTION()
	void ResetContactDamage();
};

