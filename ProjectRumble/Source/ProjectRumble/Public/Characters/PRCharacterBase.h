// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PREntityBase.h" 
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"
#include "Datas/PRCharacterDefinition.h"
#include "PRCharacterBase.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction; 
class UInputMappingContext; 
class UPRStatsComponent;
class UPRInteractionComponent;
class USphereComponent;

UCLASS()
class PROJECTRUMBLE_API APRCharacterBase : public APREntityBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APRCharacterBase();

	// We override the function from our base class to provide player-specific logic.
	virtual UPRStatsComponent* GetStatsComponent() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// -- INPUT --
	// This is the main Input Mapping Context that will be loaded for gameplay.
	// It's assigned in the Blueprint derived from this class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// Input Action for Movement (WASD). This is an asset reference.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputAction> MoveAction;

	// Input Action for Looking around (Mouse). This is an asset reference.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputAction> LookAction;

	// Input Action for Jumping.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputAction> JumpAction;

	// Input Action for Debug Damage (for testing purposes).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputAction> DebugDamageAction;

	// Input Action for Interacting with objects.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Input")
	TObjectPtr<UInputAction> InteractAction;

	// -- CORE FUNCTIONS --
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_Controller() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnStatsComponentReady(UPRStatsComponent* ReadyStatsComp);

	// -- INPUT HANDLING FUNCTIONS --
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** A simple function to apply debug damage to this character. */
	void TakeDebugDamage();

	/** Handles interaction input. */
	void Interact();

	/** [SERVER] The actual implementation of the interaction logic, runs only on the server. */
	UFUNCTION(Server, Reliable)
	void Server_Interact();

	// -- INITIALIZATION FUNCTIONS --
	/** Initializes the character's properties from its assigned CharacterDefinition Data Asset. */
	void InitializeFromDataAsset();

	/** Sets up the Enhanced Input System for this player. */
	void InitializeInput();

	// -- HANDLING FUNCTIONS --
	virtual void OnHealthChanged(float CurrentHealth, float MaxHealth) override;

	UFUNCTION()
	void OnStatChanged(FGameplayTag StatTag, float NewValue);

	UFUNCTION()
	void OnPickupSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnDeath() override;

	// -- COMPONENTS --
	// The Spring Arm (or camera boom) positions the camera behind the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	// The camera that follows the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	TObjectPtr<UPRInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rumble | Components")
	USphereComponent* PickupSphere;
	// --- CAMERA SETTINGS ---
	// These values will be exposed to our Blueprint class, so we can tweak them without recompiling.

	/** The lowest angle the camera can look down to, in degrees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Camera")
	float CameraPitchMin = -70.0f;

	/** The highest angle the camera can look up to, in degrees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Camera")
	float CameraPitchMax = 45.0f;

	// -- CHARACTER DATA --
	// This holds the data asset that defines this character's identity (mesh, stats, etc.)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rumble | Character")
	TObjectPtr<UPRCharacterDefinition> CharacterDefinition;

	UPROPERTY(EditDefaultsOnly, Category = "Rumble | Movement")
	float BaseJumpZVelocity = 700.0f;

	float BaseGravityScale = 1.0f;

private:
	// The cached pointer for performance now lives here, where it's needed.
	UPROPERTY()
	mutable TObjectPtr<UPRStatsComponent> CachedStatsComponent;

	void InitializeCharacter();
};



