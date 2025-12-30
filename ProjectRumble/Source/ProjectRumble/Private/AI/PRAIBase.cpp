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
#include <GameModes/PRGameMode.h>
#include <Game/PRGameState.h>
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Actors/PRBaseAttack.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include <Player/PRPlayerState.h>
#include "Components/PRSessionTrackerComponent.h"

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

	DamageInteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageInteractionSphere"));
	DamageInteractionSphere->SetupAttachment(RootComponent);

	DamageInteractionSphere->SetSphereRadius(60.0f);

	/*GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APRAIBase::OnHit);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APRAIBase::OnEndOverlap);*/

	DamageInteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &APRAIBase::OnDamageSphereOverlap);
	DamageInteractionSphere->OnComponentEndOverlap.AddDynamic(this, &APRAIBase::OnEndOverlap);
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

	if (bIsFlyingEnemy)
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			MoveComp->SetMovementMode(MOVE_Flying); 
			MoveComp->BrakingDecelerationFlying = 1000.f;
		}
	}

	OnRep_TintColor();

	InitializeStats();

	// Start the distance culling timer only on the server.
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(CullingTimerHandle, this, &APRAIBase::CheckDistanceCulling, 2.0f, true, FMath::RandRange(0.0f, 2.0f));
	}
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

	EnemyName = AIStatsRow->DisplayName;

	// 2. GET MULTIPLIER: Get the global difficulty multiplier from the GameState.
	float GlobalDifficulty = 1.0f; // Default safety value.
	if (APRGameState* PRGameState = GetWorld()->GetGameState<APRGameState>())
	{
		GlobalDifficulty = PRGameState->GetActiveDifficultyMultiplier();
	}
	
	// 2. COMBINE MULTIPLIERS
    // Global Difficulty * Endless Multiplier
    // e.g., 6.0 (Max Difficulty) * 1.5 (Endless Min 5) = 9.0x Stats
	float FinalMultiplier = GlobalDifficulty * EndlessMultiplier;

	// 3. INITIALIZE COMPONENT: Pass the base stats and multiplier to the StatsComponent.
	if (UPRStatsComponent* StatsComp = GetStatsComponent())
	{
		// The StatsComponent will handle applying the multiplier internally.
		// We pass the RAW BaseStats array from the Data Table.
		StatsComp->InitializeForAI(AIStatsRow->BaseStats, FinalMultiplier);
	}

	// 4. UPDATE AI CONTROLLER (e.g., Movement Speed)
	// The StatsComponent now has the correct, difficulty-modified speed.
	// We call this Blueprint Event to allow the AI's Blueprint to read the new speed 
	// from its StatsComponent and set it on the Blackboard or Movement Component.
	BP_SetDifficultyStats(FinalMultiplier);

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

	// Store the last attacker controller for kill credit etc.
	if (EventInstigator)
	{
		LastAttackerController = EventInstigator;
	}

	return ActualDamage;
}

void APRAIBase::CheckDistanceCulling()
{
	// Find the closest player character.
	AActor* Target = nullptr;

	// If we have a blackboard target, use that first (Fast).
	if (AAIController* AIC = Cast<AAIController>(GetController()))
	{
		if (AIC->GetBlackboardComponent())
		{
			Target = Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(FName("TargetActor")));
		}
	}

	// If no blackboard target, fallback to player 0.
	if (!Target)
	{
		Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	}

	if (Target)
	{
		float DistSq = FVector::DistSquared(GetActorLocation(), Target->GetActorLocation());
		if (DistSq > (CullingDistance * CullingDistance))
		{
			PlayCullingEffect();

			// Security: We can stop the timer in case BP didn't implement it or forgot, but it's best to trust BP.
			GetWorld()->GetTimerManager().ClearTimer(CullingTimerHandle);
		}
	}
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

	// Make sure it doesnt apply damage on death.
	bCanApplyContactDamage = false; 
	GetWorld()->GetTimerManager().ClearTimer(ContactDamageTimerHandle); 
	GetWorld()->GetTimerManager().ClearTimer(AttackDelayTimerHandle);

	if (DamageInteractionSphere)
	{
		DamageInteractionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DamageInteractionSphere->SetGenerateOverlapEvents(false);
	}

	if (LootComponent)
	{
		LootComponent->DropLoot();
	}

	if (LastAttackerController.IsValid())
	{
		if (APRPlayerState* KillerPS = LastAttackerController->GetPlayerState<APRPlayerState>())
		{
			if (KillerPS->TrackerComponent)
			{
				KillerPS->TrackerComponent->AddStat(NativeGameplayTags::Tracker::TAG_Tracker_Main_Combat_Kills, 1.0f);
			}
		}
	}

	// We could add raggdoll but its poitnless in a game like this, so we destroy it.
	PlayCullingEffect();
}

void APRAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APRAIBase::OnDamageSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check Authority & Damage flag
	if (HasAuthority() && bCanApplyContactDamage)
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OtherActor))
		{
			ContactTarget = Player;
			ApplyContactDamage(Player);
		}
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

void APRAIBase::ApplyContactDamage(APRCharacterBase* TargetPlayer)
{
	// --- 1. PREPARE THE DAMAGE DATA ---
	// Create an instance of the struct that ApplyRumbleDamage expects.
	FDamageCalculationResult DamageResult;

	DamageResult.FinalDamage = ContactDamage; // The simple float damage value from our AI.
	DamageResult.bWasCriticalHit = false;   // Contact damage can't crit (design decision).

	// --- 2. APPLY DAMAGE AND KNOCKBACK ---
	// Player's position - AI position = Direction from AI to Player.
	FVector DirectionToPlayer = TargetPlayer->GetActorLocation() - GetActorLocation();
	DirectionToPlayer.Normalize();
	
	// Tweak: Add a tiny bit of upward force so ground friction doesn't eat the knockback immediately.
	DirectionToPlayer.Z = 0.2f;
	DirectionToPlayer.Normalize();

	UPRGameplayStatics::ApplyRumbleDamage(
		this,
		TargetPlayer,
		ContactDamage,
		DamageResult,
		FGameplayTag::EmptyTag,
		GetController(),
		this,
		nullptr,
		DirectionToPlayer,
		KnockbackStrengthToPlayer,
		ContactStunChance,
		ContactStunDuration
	);
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
	bCanApplyContactDamage = true;

	// Instead of manual target or distance control, ask the Sphere Component:
	// “Is there currently a Player (APRCharacterBase) inside you?”
	TArray<AActor*> OverlappingActors;
	if (DamageInteractionSphere)
	{
		// Only get actors of type APRCharacterBase
		DamageInteractionSphere->GetOverlappingActors(OverlappingActors, APRCharacterBase::StaticClass());
	}

	if (OverlappingActors.Num() > 0)
	{
		// Usually there should only be one player overlapping, but just in case, we take the first one.
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OverlappingActors[0]))
		{
			// Update the contact target.
			ContactTarget = Player;

			ApplyContactDamage(Player);
		}
	}
	else
	{
		// Clear
		ContactTarget = nullptr;
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

float APRAIBase::GetAttackRange() const
{
	if (StatsComponent_AI)
	{
		// Fetch the value using the tag we defined.
		float Range = StatsComponent_AI->GetStatValue(NativeGameplayTags::Stats::AI::TAG_Stat_AI_AttackRange);

		// If range is 0 (stat missing or not set), default to a melee range.
		return (Range > 0.f) ? Range : 100.0f;
	}

	return 100.0f; // Safe default
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

void APRAIBase::PerformAttack(AActor* TargetActor)
{
	if (!HasAuthority() || !RangedProjectileClass || !TargetActor) return;

	if (bIsAttacking) return;

	if (GetWorld()->GetTimerManager().IsTimerActive(AttackDelayTimerHandle)) return;

	bIsAttacking = true;

	// 1. Calculate target direction
	// Not slightly above the ground, but right where your foot lands (the floor).
	FVector TargetLocation = TargetActor->GetActorLocation();
	TargetLocation.Z -= 50.0f; // Lower to ground level 

	CachedTargetLocation = TargetLocation;

	// 2. Calculate Spawn Location (e.g., slightly in front of the AI)
	FVector SpawnLoc = GetActorLocation() + (GetActorUpVector() * 100.0f); // Above head
	FRotator SpawnRot = FRotator::ZeroRotator;

	AActor* Indicator = nullptr;
	// --- (INDICATOR) ---
	if (AttackIndicatorClass)
	{
		Indicator = GetWorld()->SpawnActor<AActor>(AttackIndicatorClass, TargetLocation, FRotator::ZeroRotator);
	}
	// Set the indicator's duration until the bullet falls (or slightly longer).
	if (Indicator)
	{
		Indicator->SetLifeSpan(3.0f); 
	}

	UE_LOG(LogTemp, Log, TEXT("AI %s is attacking towards location %s"), *GetName(), *CachedTargetLocation.ToString());

	// 3. Start Timer (e.g., fire after 1.5 seconds)
	// This duration is the time required for the player to escape.
	float Delay = 1.5f;
	GetWorld()->GetTimerManager().SetTimer(
		AttackDelayTimerHandle,
		this,
		&APRAIBase::SpawnRangedProjectile,
		Delay,
		false
	);
}

void APRAIBase::SetEnemyColor(FLinearColor NewColor)
{
	// Only Works Server
	if (HasAuthority())
	{
		TintColor = NewColor;

		// Update immediately on Server
		OnRep_TintColor();
	}
}

void APRAIBase::SetEndlessBuffs(float InMultiplier, FLinearColor InColor)
{
	if (!HasAuthority()) return;

	EndlessMultiplier = InMultiplier;

	// Apply Color immediately
	SetEnemyColor(InColor);
}

void APRAIBase::OnRep_TintColor()
{
	// This function is called automatically on the Client and manually on the Server.
	// 
	// Assuming our material has a Vector Parameter named "Tint" or "BodyColor".
	// "FlashColor" was for hit feedback, let's use "Tint" for base color.
	FName ColorParamName = TEXT("Tint"); 

	// The DynamicMaterials array was being populated in BeginPlay.
	// If this function runs before BeginPlay (which is possible), the materials may need to be created here.
	// But generally, BeginPlay runs after DeferredSpawn and FinishSpawningActor, then the variables arrive.

	// Safety
	if (DynamicMaterials.Num() == 0 && GetMesh())
	{
		//@TODO: Consider moving this logic to a separate function to avoid duplication with BeginPlay.
	}
	for (UMaterialInstanceDynamic* MID : DynamicMaterials)
	{
		if (MID)
		{
			MID->SetVectorParameterValue(ColorParamName, TintColor);
		}
	}
}

void APRAIBase::ResetAttackState()
{
	bIsAttacking = false;
}

void APRAIBase::SpawnRangedProjectile()
{
	// Control
	if (!RangedProjectileClass) return;

	UE_LOG(LogTemp, Log, TEXT("AI %s is attacking towards location %s "), *GetName(), *CachedTargetLocation.ToString());

	// 1. Spawn Points (Above Head)
	FVector SpawnLoc = GetActorLocation() + (GetActorUpVector() * 100.0f);

	// --- NEW LOGIC: CALCULATE VELOCITY BY TIME ---

	FVector TossVelocity = FVector::ZeroVector;
	const float GravityZ = GetWorld()->GetGravityZ(); // Usually -980.0f
	
	// Formula: V0 = (Target - Start - (0.5 * g * t^2)) / t
	FVector Distance = CachedTargetLocation - SpawnLoc;
	FVector GravityComp = FVector(0, 0, 0.5f * GravityZ * FMath::Square(ProjectileFlightTime));

	// Calculate the exact velocity needed to hit the target in 'ProjectileFlightTime' seconds.
	TossVelocity = (Distance - GravityComp) / ProjectileFlightTime;

	DrawDebugLine(GetWorld(), SpawnLoc, CachedTargetLocation, FColor::Red, false, 2.0f, 0, 5.0f);

	FRotator SpawnRot = TossVelocity.Rotation();

	APRBaseAttack* Projectile = GetWorld()->SpawnActorDeferred<APRBaseAttack>(
		RangedProjectileClass,
		FTransform(SpawnRot, SpawnLoc),
		this,
		this,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	// 4. Calculate Stats
	float CalculatedDamage = 10.0f;
	float CalculatedKnockback = 500.0f;
	float ProjectileSpeed = 1000.0f;
	if (StatsComponent_AI)
	{
		CalculatedDamage = StatsComponent_AI->GetStatValue(NativeGameplayTags::Stats::AI::TAG_Stat_AI_AttackDamage);
		CalculatedKnockback = StatsComponent_AI->GetStatValue(NativeGameplayTags::Stats::Physics::TAG_Stat_Physics_Knockback);
		//ProjectileSpeed = StatsComponent_AI->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileSpeed);
		// Safety checks
		if (CalculatedDamage <= 0.f) CalculatedDamage = 1.0f;
		if (CalculatedKnockback <= 0.f) CalculatedKnockback = 100.0f;
		if (ProjectileSpeed <= 0.f) ProjectileSpeed = 500.0f;
	}

	ProjectileSpeed = TossVelocity.Size();

	if (Projectile)
	{
		// 5. Fill struct
		FPRWeaponAttackStats NewStats;
		NewStats.Damage = CalculatedDamage;
		NewStats.KnockbackMagnitude = 500.0f;
		NewStats.ProjectileSpeed = 1000.0f;

		Projectile->AttackStats = NewStats;

		if (UProjectileMovementComponent* PMC = Projectile->FindComponentByClass<UProjectileMovementComponent>())
		{
			// Gravity must be enabled for the arc to work naturally.
			PMC->ProjectileGravityScale = 1.0f;

			// Ensure local space logic is OFF so our world calculation works.
			PMC->bInitialVelocityInLocalSpace = false;

			// Remove speed limits so it doesn't clamp our calculated velocity.
			float CalcSpeed = TossVelocity.Size();
			PMC->InitialSpeed = CalcSpeed;
			PMC->MaxSpeed = 0.f; // Infinite

			// Apply the calculated velocity.
			PMC->Velocity = TossVelocity;

			// Update rotation to match velocity immediately.
			Projectile->SetActorRotation(TossVelocity.Rotation());

			PMC->UpdateComponentVelocity();
		}

		// Update Recovery Timer based on the FIXED flight time.
		// We wait exactly flight time + small buffer before resetting state.
		GetWorld()->GetTimerManager().SetTimer(
			AttackRecoveryTimerHandle,
			this,
			&APRAIBase::ResetAttackState,
			ProjectileFlightTime + 0.2f, // Add small buffer
			false
		);

		UGameplayStatics::FinishSpawningActor(Projectile, FTransform(SpawnRot, SpawnLoc));
	}
	else
	{
		// If spawning failed, reset attack state immediately.
		ResetAttackState();
	}
}

void APRAIBase::Multicast_PlayHitFlash_Implementation()
{
	PlayHitFlash();
}

void APRAIBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APRAIBase, TintColor);
}