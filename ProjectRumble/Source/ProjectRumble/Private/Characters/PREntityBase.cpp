// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PREntityBase.h"
#include "Components/PRStatsComponent.h"
#include "Components/CapsuleComponent.h"
#include <Player/PRPlayerState.h>
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APREntityBase::APREntityBase()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UPRStatsComponent* APREntityBase::GetStatsComponent() const
{
	// If this entity is NOT a player-controlled character (e.g., an AI),
	// it won't have a PlayerState. In that case, it should have its own StatsComponent.
	// We will handle this in the APR_AIBase class.
	// For now, we return a component attached to this actor as a fallback.
	return FindComponentByClass<UPRStatsComponent>();
}

// Called when the game starts or when spawned
void APREntityBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float APREntityBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Call the parent class's TakeDamage function first.
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// If damage was actually applied, pass it to our stats component to handle health reduction.
	if (UPRStatsComponent* MyStatsComponent = GetStatsComponent())
	{
		if (ActualDamage > 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("--- EntityBase::TakeDamage() --- Applying %.2f damage to StatsComponent."), ActualDamage);
			// Tell the component to handle the logic.
			MyStatsComponent->ApplyDamage(ActualDamage);
		}
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
	// Base implementation can handle universal death logic.
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	
}