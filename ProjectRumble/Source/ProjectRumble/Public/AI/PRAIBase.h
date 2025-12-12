// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PREntityBase.h"
#include "PRAIBase.generated.h"

class UPRStatsComponent;
class APRCharacterBase;
class APRXpShard;
class UPRLootComponent; 
class APRBaseAttack;
class UBehaviorTree;
class AActor;

UCLASS()
class PROJECTRUMBLE_API APRAIBase : public APREntityBase
{
	GENERATED_BODY()
	
public:
	APRAIBase();

	
	/** Returns the Gameplay Tags associated with this AI. */
	UFUNCTION(BlueprintPure, Category = "AI")
	const FGameplayTagContainer& GetAITags() const { return AITags; }

	// Getter for the Controller
	UBehaviorTree* GetBehaviorTree() const { return EnemyBehaviorTree; }

	/**
	* Retrieves the current Attack Range from the Stats Component.
	* Returns a default melee range if the stat is missing.
	*/
	UFUNCTION(BlueprintPure, Category = "AI|Combat")
	float GetAttackRange() const;

	/**
	 * Re-applies the difficulty multiplier to all stats.
	 * Called by the GameMode when the global difficulty changes mid-game.
	 */
	UFUNCTION(BlueprintCallable, Category = "AI|Difficulty")
	void UpdateDifficultyMultiplier(float NewDifficultyMultiplier);

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayHitFlash();

	/** Triggers the attack logic (Spawns projectile). Called by BTTask. */
	UFUNCTION(BlueprintCallable, Category = "AI|Combat")
	void PerformAttack(AActor* TargetActor);

protected:
	// -- COMPONENTS --
	// The AI has its own StatsComponent directly on itself.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<UPRStatsComponent> StatsComponent_AI; // Renamed to avoid confusion with the inherited pointer name.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRLootComponent> LootComponent;

	// A slightly larger sphere designated ONLY for detecting overlap damage.
	// This separates physics blocking from damage logic.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* DamageInteractionSphere;

	/** The specific Behavior Tree this enemy type uses. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> EnemyBehaviorTree;

	// -- COMBAT --
	// The projectile class to spawn for ranged attacks (Assigned in BP_Cactus).
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	TSubclassOf<APRBaseAttack> RangedProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	TSubclassOf<AActor> AttackIndicatorClass;

	// The damage this AI deals on contact.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactDamage = 5.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactStunDuration = 0.0f; 

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float ContactStunChance = 0.0f;

	// How often (in seconds) to apply contact damage while overlapping.
	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Combat")
	float DamageInterval = 0.5f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Combat")
	float KnockbackStrengthToPlayer = 50.0f;

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

	bool bIsAttacking = false;

	// --- TIMERS ---
	// The timer handle to manage the duration of the flash effect.
	FTimerHandle FlashTimerHandle;

	// The timer handle for applying contact damage.
	FTimerHandle ContactDamageTimerHandle;

	FTimerHandle AttackDelayTimerHandle;

	// The timer handle for projectile
	FTimerHandle AttackRecoveryTimerHandle;

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
	void OnDamageSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/*UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);*/

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

	UFUNCTION()
	void ResetAttackState();

	void UpdateMovementSpeed();

	// The main firing function that will run when the timer expires.
	void SpawnRangedProjectile();

	FVector CachedTargetLocation;

};

