// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRTypes.h"
#include "PRBaseAttack.generated.h"

class UAudioComponent;
class USoundBase;
class USphereComponent;

UCLASS()
class PROJECTRUMBLE_API APRBaseAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRBaseAttack();

	// --- COMPONENTS ---

	// Root Component olarak kullanýlacak Sphere Collision. 
	// Diðer Projectile'larda (Axe, Arrow) deðiþtirilebilir.
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
