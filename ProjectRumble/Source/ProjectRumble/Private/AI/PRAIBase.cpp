// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/PRAIBase.h"
#include "Components/PRStatsComponent.h"
#include "Characters/PRCharacterBase.h" 
#include "Kismet/GameplayStatics.h" 
#include "AI/PRAIController.h"
#include "Components/CapsuleComponent.h"
#include "FunctionLibrary/PRGameplayStatics.h"
#include "Actors/PRXpShard.h"
#include "PRGameplayTags.h"
#include "Components/PRLootComponent.h"
#include "Components/PRStatsComponent.h"
#include <GameModes/PRGameMode.h>
#include <Game/PRGameState.h>
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APRAIBase::APRAIBase()
{
	// This actor needs to be replicated.
	bReplicates = true;

	// For smooth movement on clients, this is also crucial.
	SetReplicateMovement(true);
	// AI creates its own StatsComponent.
	StatsComponent_AI = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));
	LootComponent = CreateDefaultSubobject<UPRLootComponent>(TEXT("LootComponent"));

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
	if (USkeletalMeshComponent* MyMesh = GetMesh())
	{
		const int32 NumMaterials = MyMesh->GetNumMaterials();

		// Clear any old dynamic materials, just in case
		DynamicMaterials.Empty();

		// Loop through all material slots
		for (int32 i = 0; i < NumMaterials; ++i)
		{
			// Get the original material from the slot
			UMaterialInterface* OriginalMaterial = MyMesh->GetMaterial(i);
			if (OriginalMaterial)
			{
				// Create a dynamic instance of that material
				UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(OriginalMaterial, this);

				// Set the new dynamic instance back onto the mesh slot
				MyMesh->SetMaterial(i, MID);

				// Add the new MID to our array for later use
				DynamicMaterials.Add(MID);
			}
		}

		if (DynamicMaterials.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("EntityBase on %s has no materials to create dynamic instances from!"), *GetName());
		}
		
		/*UMaterialInterface* OriginalMaterial = GetMesh()->GetMaterial(0);
		if (OriginalMaterial)
		{
			DynamicMaterial = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
			GetMesh()->SetMaterial(0, DynamicMaterial);
		}*/
	}

	InitializeStats();
}

void APRAIBase::InitializeStats()
{
	// Initialization logic should only run on the server. 
	// The stats will be replicated to clients via the StatsComponent.
	if (!HasAuthority())
	{
		return;
	}

	// 1. READ DATA: Get the AI's base stat row from the Data Table.
	if (!AllEnemyStatsTable || DataTableID.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("APRAIBase '%s' is missing AllEnemyStatsTable or DataTableID!"), *GetName());
		return;
	}

	const FAIStats* AIStatsRow = AllEnemyStatsTable->FindRow<FAIStats>(DataTableID, TEXT("AI Stats Initialization"));
	if (!AIStatsRow)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find row '%s' in AllEnemyStatsTable for %s!"), *DataTableID.ToString(), *GetName());
		return;
	}

	// 2. GET MULTIPLIER: Get the global difficulty multiplier from the GameState.
	float DifficultyMultiplier = 1.0f; // Default safety value.
	if (APRGameState* PRGameState = GetWorld()->GetGameState<APRGameState>())
	{
		DifficultyMultiplier = PRGameState->GetActiveDifficultyMultiplier();
	}

	// 3. INITIALIZE COMPONENT: Pass the base stats and multiplier to the StatsComponent.
	if (UPRStatsComponent* StatsComp = GetStatsComponent())
	{
		// The StatsComponent will handle applying the multiplier internally.
		// We pass the RAW BaseStats array from the Data Table.
		StatsComp->InitializeForAI(AIStatsRow->BaseStats, DifficultyMultiplier);
	}

	// 4. UPDATE AI CONTROLLER (e.g., Movement Speed)
	// The StatsComponent now has the correct, difficulty-modified speed.
	// We call this Blueprint Event to allow the AI's Blueprint to read the new speed 
	// from its StatsComponent and set it on the Blackboard or Movement Component.
	BP_SetDifficultyStats(DifficultyMultiplier);

	// We set Movement Speed After Difficulty, because it will read the updated stat value.
	UpdateMovementSpeed();
}

float APRAIBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority()) return 0.f;

	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		// Play the flash effect whenever damage is taken.
		Multicast_PlayHitFlash();
	}

	return ActualDamage;
}

void APRAIBase::PlayHitFlash()
{
	// Loop through all our dynamic materials and set the parameter on each one.
	for (UMaterialInstanceDynamic* MID : DynamicMaterials)
	{
		if (MID)
		{
			MID->SetVectorParameterValue(FName("FlashColor"), FLinearColor::White);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &APRAIBase::StopHitFlash, 0.1f, false);

	//if (DynamicMaterial)
	//{
	//	DynamicMaterial->SetVectorParameterValue(FName("FlashColor"), FLinearColor::White);

	//	// Set a timer to stop the flash after a short duration.
	//	GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &APRAIBase::StopHitFlash, 0.1f, false);
	//}
}

void APRAIBase::StopHitFlash()
{
	// Loop through all our dynamic materials and reset the color on each one.
	for (UMaterialInstanceDynamic* MID : DynamicMaterials)
	{
		if (MID)
		{
			MID->SetVectorParameterValue(FName("FlashColor"), FLinearColor::Black);
		}
	}

	//if (DynamicMaterial)
	//{
	//	// Reset the color back to black.
	//	DynamicMaterial->SetVectorParameterValue(FName("FlashColor"), FLinearColor::Black);
	//}
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
	// Find our loot component and tell it to do its job.
	if (LootComponent)
	{
		LootComponent->DropLoot();
	}

	// Make the AI's body disappear after 5 seconds.
	SetLifeSpan(3.0f);
}

void APRAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	// --- 1. PREPARE THE DAMAGE DATA ---
	// Create an instance of the struct that ApplyRumbleDamage expects.
	FDamageCalculationResult DamageResult;

	DamageResult.FinalDamage = ContactDamage; // The simple float damage value from our AI.
	DamageResult.bWasCriticalHit = false;   // Contact damage can't crit (design decision).

	// --- 2. APPLY DAMAGE AND KNOCKBACK ---
	FVector DirectionFromAI = TargetPlayer->GetActorLocation() - GetActorLocation();
	DirectionFromAI.Normalize();
	
	UPRGameplayStatics::ApplyRumbleDamage(this,TargetPlayer, ContactDamage,DamageResult , GetController(), this, nullptr, DirectionFromAI, 0, ContactStunChance, ContactStunDuration);

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

void APRAIBase::UpdateMovementSpeed()
{
	if (UPRStatsComponent* StatsComp = GetStatsComponent())
	{
		float NewSpeed = StatsComp->GetStatValue(NativeGameplayTags::Stats::Mobility::TAG_Stat_Mobility_MovementSpeed_Base);

		if (NewSpeed > 0.f)
		{
			if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
			{
				MoveComp->MaxWalkSpeed = NewSpeed;
			}
		}
	}
}

void APRAIBase::UpdateDifficultyMultiplier(float NewDifficultyMultiplier)
{
	// This function re-reads the Data Table and re-initializes the StatsComponent
	// with the new multiplier. It's essentially a re-run of the initialization logic.

	if (!AllEnemyStatsTable || DataTableID.IsNone()) return;

	const FAIStats* AIStatsRow = AllEnemyStatsTable->FindRow<FAIStats>(DataTableID, TEXT("AI Stats Update"));
	if (!AIStatsRow) return;

	if (UPRStatsComponent* StatsComp = GetStatsComponent())
	{
		StatsComp->InitializeForAI(AIStatsRow->BaseStats, NewDifficultyMultiplier);
	}

	// Also update the AI Controller.
	BP_SetDifficultyStats(NewDifficultyMultiplier);

	UpdateMovementSpeed();
}

void APRAIBase::Multicast_PlayHitFlash_Implementation()
{
	PlayHitFlash();
}
