// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PREntityBase.h"
#include "PRAIBase.generated.h"

class UPRStatsComponent;
class APRCharacterBase;
class APRXpShard;
class UPRLootComponent; 

UCLASS()
class PROJECTRUMBLE_API APRAIBase : public APREntityBase
{
	GENERATED_BODY()
	
public:
	APRAIBase();

	
	/** Returns the Gameplay Tags associated with this AI. */
	UFUNCTION(BlueprintPure, Category = "AI")
	const FGameplayTagContainer& GetAITags() const { return AITags; }

	/**
	 * Re-applies the difficulty multiplier to all stats.
	 * Called by the GameMode when the global difficulty changes mid-game.
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|Difficulty")
	void UpdateDifficultyMultiplier(float NewDifficultyMultiplier);

protected:
	// -- COMPONENTS --
	// The AI has its own StatsComponent directly on itself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<UPRStatsComponent> StatsComponent_AI; // Renamed to avoid confusion with the inherited pointer name.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRLootComponent> LootComponent;

	// -- COMBAT --
	// The damage this AI deals on contact.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactDamage = 5.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactStunDuration = 0.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactStunChance = 0.0f;

	// How often (in seconds) to apply contact damage while overlapping.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float DamageInterval = 2.0f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Combat")
	float KnockbackStrengthToPlayer = 500.0f;

	// The Data Table that defines all possible stats and their default values.
	// This should be assigned in the Blueprint derived from this component.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Config")
	TObjectPtr<UDataTable> AllEnemyStatsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Config")
	FName DataTableID;
	// The player we are currently in contact with.
	UPROPERTY()
	TObjectPtr<APRCharacterBase> ContactTarget;

	// A pointer to the dynamic material instance for hit flash effects.
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	// An array to hold all dynamic material instances for this entity.
	UPROPERTY()
	TArray<TObjectPtr<UMaterialInstanceDynamic>> DynamicMaterials;

	UPROPERTY(BlueprintReadWrite, Category = "Rumble | Combat")
	bool bCanApplyDamage = true;

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

	UFUNCTION()
	void InitializeStats();

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

	UFUNCTION(BlueprintImplementableEvent)

	void BP_ResetDamage();

	/**
	 * Blueprint-implementable event called after stats have been initialized with difficulty.
	 * Allows the AI's Blueprint to react to the new stats (e.g., updating movement speed on the Blackboard).
	 * @param DifficultyMultiplier The multiplier that was just applied, for convenience.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "AI|Difficulty")
	void BP_SetDifficultyStats(float DifficultyMultiplier);

};

