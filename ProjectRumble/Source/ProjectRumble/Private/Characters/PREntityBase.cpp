// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PREntityBase.h"
#include "Components/PRStatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APREntityBase::APREntityBase()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Stats Component. This will exist on both Player and AI.
	StatsComponent = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));

}

// Called when the game starts or when spawned
void APREntityBase::BeginPlay()
{
	Super::BeginPlay();

	// It's crucial to bind our functions to the delegates from the StatsComponent.
	// This is how this class "listens" to events happening inside its component.
	if (StatsComponent)
	{
		StatsComponent->OnHealthChangedDelegate.AddDynamic(this, &APREntityBase::OnHealthChanged);
		StatsComponent->OnDeathDelegate.AddDynamic(this, &APREntityBase::OnDeath);
	}
	
}

float APREntityBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Call the parent class's TakeDamage function first.
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// If damage was actually applied, pass it to our stats component to handle health reduction.
	if (ActualDamage > 0.f && StatsComponent)
	{
		StatsComponent->ApplyDamage(ActualDamage);
	}

	return ActualDamage;
}

void APREntityBase::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	// This is a great place for logic that should happen for ANY entity when its health changes.
	// For example, playing a "hurt" sound or flashing a material red.
	// We'll leave it empty for now, but child Blueprints can override this event.
	UE_LOG(LogTemp, Log, TEXT("%s Health Changed: %f / %f"), *GetName(), CurrentHealth, MaxHealth);
}

void APREntityBase::OnDeath()
{
	// Base implementation for death.
	// We can add logic here like detaching the controller and enabling ragdoll.
	// Child classes can override this to add player-specific (e.g., show game over screen) or AI-specific logic.
	UE_LOG(LogTemp, Warning, TEXT("%s has died!"), *GetName());

	// Example: Disable collision and stop movement.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
}