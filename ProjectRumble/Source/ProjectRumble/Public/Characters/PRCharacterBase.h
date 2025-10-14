// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PREntityBase.h" 
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include <Datas/PRCharacterDefinition.h>
#include "PRCharacterBase.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction; 
class UInputMappingContext; 
class UPRStatsComponent;

UCLASS()
class PROJECTRUMBLE_API APRCharacterBase : public APREntityBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APRCharacterBase();

	// We override the function from our base class to provide player-specific logic.
	virtual UPRStatsComponent* GetStatsComponent() const override;
protected:
	// -- INPUT --
	// This is the main Input Mapping Context that will be loaded for gameplay.
	// It's assigned in the Blueprint derived from this class.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// Input Action for Movement (WASD). This is an asset reference.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// Input Action for Looking around (Mouse). This is an asset reference.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	// Input Action for Jumping.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	// Input Action for Debug Damage (for testing purposes).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> DebugDamageAction;

	// -- CORE FUNCTIONS --
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// -- INPUT HANDLING FUNCTIONS --
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** A simple function to apply debug damage to this character. */
	void TakeDebugDamage();

	// -- INITIALIZATION FUNCTIONS --
	/** Initializes the character's properties from its assigned CharacterDefinition Data Asset. */
	void InitializeFromDataAsset();

	/** Sets up the Enhanced Input System for this player. */
	void InitializeInput();

	// -- HANDLING FUNCTIONS --
	virtual void OnHealthChanged(float CurrentHealth, float MaxHealth) override;

	virtual void OnDeath() override;

	// -- COMPONENTS --
	// The Spring Arm (or camera boom) positions the camera behind the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	// The camera that follows the character.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	// --- CAMERA SETTINGS ---
	// These values will be exposed to our Blueprint class, so we can tweak them without recompiling.

	/** The lowest angle the camera can look down to, in degrees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraPitchMin = -70.0f;

	/** The highest angle the camera can look up to, in degrees. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraPitchMax = 45.0f;

	// -- CHARACTER DATA --
	// This holds the data asset that defines this character's identity (mesh, stats, etc.)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	TObjectPtr<UPRCharacterDefinition> CharacterDefinition;

private:
	// The cached pointer for performance now lives here, where it's needed.
	UPROPERTY()
	mutable TObjectPtr<UPRStatsComponent> CachedStatsComponent;
};



