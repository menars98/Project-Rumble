// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRTypes.h"
#include "PRBaseAttack.generated.h"

class UAudioComponent;
class USoundBase;
class USphereComponent;
class UProjectileMovementComponent;
class UPRItemDefinition;

UCLASS()
class PROJECTRUMBLE_API APRBaseAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRBaseAttack();

	// --- COMPONENTS ---

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> RootCollision;

	/** Component used to play looping or persistent sounds (like Aura buzz or projectile travel sound). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComp;

	// --- PROPERTIES ---

	/**
	 * The stats for this specific attack instance.
	 * ExposeOnSpawn is CRITICAL here, allowing the spawning BP (Weapon Item) to populate this struct.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack|Stats", meta = (ExposeOnSpawn = "true"))
	FPRWeaponAttackStats AttackStats;

	/**
	* The definition of the item (Weapon) that spawned this attack.
	* Used to retrieve the ItemIdentityTag for stat tracking.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rumble|Stats", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UPRItemDefinition> SourceItemDef;

	// --- AUDIO PROPERTIES ---

	/** Sound to play when the attack is spawned (e.g., Axe Throw, Arrow release). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack|Audio")
	TObjectPtr<USoundBase> SpawnSound;

	/** Sound to play when the attack impacts a target (e.g., Hit sound). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack|Audio")
	TObjectPtr<USoundBase> ImpactSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// --- FUNCTIONALITY ---

	// Applies statuses regardless of damage.
	void HandleStatusApplication(AActor* TargetActor);
	/**
	 * The central function to execute the damage logic.
	 * This is called in response to an Overlap event.
	 */
	UFUNCTION(BlueprintCallable, Category = "Attack|Damage")
	void ApplyDamageToTarget(AActor* TargetActor);
	/**
	 * The core overlap function. Marked as BlueprintNativeEvent to allow BP overriding
	 * while retaining C++ base implementation (if desired).
	 */
	UFUNCTION(BlueprintNativeEvent, Category = "Attack|Lifecycle")
	void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnAttackOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Rumble|Combat")
	void HandleOverlap(AActor* OtherActor);

	/**
	 * Attempts to find a new target nearby and redirect the projectile.
	 * @param HitActor The actor we just hit (to ignore).
	 * @return True if a valid bounce target was found.
	 */
	bool TryBounce(AActor* HitActor);

	UPROPERTY(EditDefaultsOnly, Category = "Rumble|Combat")
	float BounceSearchRadius = 1000.0f;

	UPROPERTY()
	TArray<AActor*> HitHistory;

	UPROPERTY()
	TMap<AActor*, double> DamageCooldownMap;

	/**
	* If true, knockback direction is based on projectile velocity (Arrows, Spears).
	* If false, knockback is radial from the center of the actor (Explosions, Rocks, Auras).
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rumble|Combat")
	bool bUseVelocityForKnockback = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
