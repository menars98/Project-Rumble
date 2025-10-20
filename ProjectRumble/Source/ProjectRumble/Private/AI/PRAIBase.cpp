// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PRAIBase.h"
#include "Components/PRStatsComponent.h"
#include "Characters/PRCharacterBase.h" 
#include "Kismet/GameplayStatics.h" 
#include "AI/PRAIController.h"
#include "Components/CapsuleComponent.h"
#include <FunctionLibrary/PRGameplayStatics.h>

APRAIBase::APRAIBase()
{
	// AI creates its own StatsComponent.
	StatsComponent_AI = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));

	// Set the default AI Controller class for ALL pawns that inherit from APRAIBase.
	AIControllerClass = APRAIController::StaticClass();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APRAIBase::OnHit);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APRAIBase::OnEndOverlap);
}

void APRAIBase::BeginPlay()
{
	Super::BeginPlay();

	if (StatsComponent_AI)
	{
		StatsComponent_AI->OnDeathDelegate.AddDynamic(this, &APRAIBase::OnDeath);
		StatsComponent_AI->OnHealthChangedDelegate.AddDynamic(this, &APRAIBase::OnHealthChanged);
	}
	// Create a dynamic material instance when the AI spawns.
	if (GetMesh())
	{
		UMaterialInterface* OriginalMaterial = GetMesh()->GetMaterial(0);
		if (OriginalMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
			GetMesh()->SetMaterial(0, DynamicMaterial);
		}
	}

}

float APRAIBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		// Play the flash effect whenever damage is taken.
		PlayHitFlash();
	}

	return ActualDamage;
}

void APRAIBase::PlayHitFlash()
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(FName("FlashColor"), FLinearColor::White);

		// Set a timer to stop the flash after a short duration.
		GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &APRAIBase::StopHitFlash, 0.1f, false);
	}
}

void APRAIBase::StopHitFlash()
{
	if (DynamicMaterial)
	{
		// Reset the color back to black.
		DynamicMaterial->SetVectorParameterValue(FName("FlashColor"), FLinearColor::Black);
	}
}

// Override to return the AI's own component.
UPRStatsComponent* APRAIBase::GetStatsComponent() const
{
	return StatsComponent_AI;
}

void APRAIBase::OnDeath()
{
	Super::OnDeath(); // Run the base logic from EntityBase (disable collision etc.).

	USkeletalMeshComponent* MyMesh = GetMesh();
	if (MyMesh)
	{
		// --- RAGDOLL LOGIC ---

		// Detach from the controller so it no longer receives AI commands
		if (Controller)
		{
			Controller->UnPossess();
		}

		// Set the collision profile to "Ragdoll" to allow it to collide with the world
		MyMesh->SetCollisionProfileName(FName("Ragdoll"));

		// Enable physics simulation on the mesh.
		// The "true" parameter tells it to wake the physics body immediately.
		MyMesh->SetSimulatePhysics(true);
	}

	// --- AWARD XP TO THE PLAYER ---
	// Get a reference to the player character. This is a simple way for single-player.
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(PlayerCharacter))
	{
		// Get the player's stats component (this will correctly get it from the PlayerState).
		if (UPRStatsComponent* PlayerStats = Player->GetStatsComponent())
		{
			PlayerStats->AddXP(XPToAward);
			UE_LOG(LogTemp, Log, TEXT("Awarded %f XP to player."), XPToAward);
		}
	}

	// Make the AI's body disappear after 5 seconds.
	SetLifeSpan(5.0f);
}

void APRAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// --- VERY SIMPLE "CHASE PLAYER" LOGIC ---
	// This is a "dumb" AI. It doesn't use navigation or behavior trees.
	// It just moves in a straight line towards the player. Good for a prototype.
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		// Get the direction from the AI to the player.
		FVector DirectionToPlayer = PlayerCharacter->GetActorLocation() - GetActorLocation();
		DirectionToPlayer.Normalize(); // Make it a unit vector (length of 1).

		// Move the AI in that direction.
		AddMovementInput(DirectionToPlayer);
	}
}

void APRAIBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// If the player is no longer touching us, clear the target.

	if (OtherActor && ContactTarget.Get() == OtherActor)
	{
		ContactTarget = nullptr;
	}
}

void APRAIBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if we hit a player and if we are currently able to deal damage.
	if (bCanApplyContactDamage)
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OtherActor))
		{
			// Store the target.
			ContactTarget = Player;

			// Call the member function ApplyContactDamage. "this->" is implicit.
			ApplyContactDamage(Player);

		}
	}
}

void APRAIBase::ApplyContactDamage(APRCharacterBase* TargetPlayer)
{
	if (!TargetPlayer) return;

	// --- 1. APPLY DAMAGE AND KNOCKBACK ---
	FVector DirectionFromAI = TargetPlayer->GetActorLocation() - GetActorLocation();
	DirectionFromAI.Normalize();
	
	UPRGameplayStatics::ApplyRumbleDamage(TargetPlayer, ContactDamage, GetController(), this, nullptr, DirectionFromAI, KnockbackStrengthToPlayer);

	// --- 2. START THE COOLDOWN ---
	// Disable our ability to deal damage immediately.
	bCanApplyContactDamage = false;

	// Set a timer to call ResetContactDamage after the interval.
	GetWorld()->GetTimerManager().SetTimer(
		ContactDamageTimerHandle,
		this,
		&APRAIBase::ResetContactDamage,
		DamageInterval,
		false // Don't loop
	);
}

void APRAIBase::ResetContactDamage()
{
	// The cooldown is over. We can now deal damage again.
	bCanApplyContactDamage = true;

	// --- CONTINUOUS DAMAGE LOGIC ---
	// If we are STILL overlapping with the target, apply damage again immediately
	// and restart the cooldown timer. This creates a damage-over-time effect while in contact.
	if (ContactTarget)
	{
		// Check if the capsule is still overlapping the target
		if (GetCapsuleComponent()->IsOverlappingActor(ContactTarget))
		{
			ApplyContactDamage(ContactTarget);
		}
	}
}
