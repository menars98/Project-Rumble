

#include "Actors/PRBaseAttack.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/PRGameplayStatics.h"
#include "Characters/PRCharacterBase.h"
#include "AI/PRAIBase.h"
#include "Components/AudioComponent.h"
#include "Components/PRStatsComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PRGameplayTags.h"
#include "ProjectRumble/ProjectRumble.h"

APRBaseAttack::APRBaseAttack()
{
	PrimaryActorTick.bCanEverTick = false;

    bReplicates = true;
    SetReplicateMovement(true);

	// Setup the default lifespan
	InitialLifeSpan = AttackStats.LifeDuration; 

    AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComp->SetupAttachment(RootCollision);
    AudioComp->bAutoActivate = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	// Default Settings(For straight-flying bullets)

	if (ProjectileMovement)
	{
		if (AttackStats.ProjectileSpeed > 0.f)
		{
			ProjectileMovement->InitialSpeed = AttackStats.ProjectileSpeed;
			ProjectileMovement->MaxSpeed = AttackStats.ProjectileSpeed;
			ProjectileMovement->UpdatedComponent = RootCollision;
			ProjectileMovement->bRotationFollowsVelocity = true;
			ProjectileMovement->bShouldBounce = false;
			ProjectileMovement->bSweepCollision = true;
			ProjectileMovement->ProjectileGravityScale = 0.f;

			// If the bullet is fired at spawn, update its velocity
			ProjectileMovement->Velocity = ProjectileMovement->Velocity.GetSafeNormal() * AttackStats.ProjectileSpeed;
		}
	}
	
}

void APRBaseAttack::BeginPlay()
{
	Super::BeginPlay();
	
	// LifeDuration, Spawn anýnda AttackStats struct'ýndan atanacaktýr.
	SetLifeSpan(AttackStats.LifeDuration);
}

void APRBaseAttack::HandleStatusApplication(AActor* TargetActor)
{
	// Validations
	if (AttackStats.StatusEffects.Num() == 0) return;

	APREntityBase* Entity = Cast<APREntityBase>(TargetActor);
	if (!Entity) return;

	UPRStatsComponent* StatsComp = Entity->GetStatsComponent();
	if (!StatsComp) return;

	// Loop through and apply each status effect
	for (const FStatusApplicationData& Status : AttackStats.StatusEffects)
	{
		if (Status.StatusTag.IsValid())
		{
			AController* InstigatorController = GetInstigator()->GetController();	
			StatsComp->AddStatusStack(Status.StatusTag, Status.StackAmount, InstigatorController);

			// Debug Log 
			// UE_LOG(LogTemp, Verbose, TEXT("Applied %s (x%d) to %s"), *Status.StatusTag.ToString(), Status.StackAmount, *TargetActor->GetName());
		}
	}
}

void APRBaseAttack::ApplyDamageToTarget(AActor* TargetActor)
{
    if (!HasAuthority()) return;
    if (!IsValid(TargetActor) || !IsValid(GetOwner())) return;

    // 
    float FinalDamage = AttackStats.Damage;
    FDamageCalculationResult DamageResult;
    DamageResult.FinalDamage = FinalDamage;

	FGameplayTag MyTag = FGameplayTag::EmptyTag;
	if (SourceItemDef)
	{
		MyTag = SourceItemDef->ItemIdentityTag;
	}


    AController* InstigatorController = nullptr;
    AActor* DamageCauser = GetOwner();
	APawn* MyInstigator = GetInstigator();

	// Check if the instigator is still alive
	if (MyInstigator)
	{
		if (APRCharacterBase* MyChar = Cast<APRCharacterBase>(MyInstigator))
		{
			if (UPRStatsComponent* Stats = MyChar->GetStatsComponent())
			{
				float CurrentHP = Stats->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health);

				if (CurrentHP <= 0.0f)
				{
					Destroy();
					return;
				}
			}
		}
	}

	// --- (PLAYER) ---
	if (APRCharacterBase* PlayerOwner = Cast<APRCharacterBase>(GetOwner()))
	{
		InstigatorController = PlayerOwner->GetController();

		if (UPRStatsComponent* PlayerStats = PlayerOwner->GetStatsComponent())
		{
			const APRAIBase* TargetAI = Cast<APRAIBase>(TargetActor);

			DamageResult = UPRGameplayStatics::CalculateFinalDamage(
				PlayerStats,
				AttackStats.Damage,
				AttackStats.CritChance,
				AttackStats.CritMultiplier,
				TargetAI
			);
			FinalDamage = DamageResult.FinalDamage;
		}
	}
	// --- (AI) ---
	else if (APRAIBase* AIOwner = Cast<APRAIBase>(GetOwner()))
	{
		InstigatorController = AIOwner->GetController();
		//We need to take damage from tag
		FinalDamage = AttackStats.Damage;
		DamageResult.FinalDamage = FinalDamage;
		DamageResult.bWasCriticalHit = false; // Don't use AI Crit (or it can be added here)
	}

	FVector KnockForce = FVector::ZeroVector;

	if (AttackStats.KnockbackMagnitude > 0.0f)
	{
		FVector KnockDir;

		// CASE 1: Hýz Bazlý (Ok, Mýzrak) - bUseVelocityForKnockback TRUE ise
		if (bUseVelocityForKnockback && ProjectileMovement && !ProjectileMovement->Velocity.IsNearlyZero())
		{
			KnockDir = ProjectileMovement->Velocity.GetSafeNormal2D(); // Sadece Yatay Yön
		}
		// CASE 2: Konum Bazlý (Rock, Aura, Puddle) - bUseVelocityForKnockback FALSE ise
		else
		{
			// Mermiden -> Düþmana olan yön
			KnockDir = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal2D(); // Z'yi otomatik sýfýrlar
		}

		// 1. Yatay Gücü Hesapla
		KnockForce = KnockDir * AttackStats.KnockbackMagnitude;

		// 2. Dikey (Z) Gücü MANUEL Ekle (Patlama etkisi deðil, hafif zýplatma)
		// Magnitude ne olursa olsun, düþmaný yerden 300 birim yukarý zýplat ki sürtünme onu tutamasýn.
		KnockForce.Z = 300.0f;
	}

	// --- Apply Damage ---
	UPRGameplayStatics::ApplyRumbleDamage(
		this,
		TargetActor,
		FinalDamage,
		DamageResult,
		MyTag,
		InstigatorController,
		DamageCauser,
		UDamageType::StaticClass(),
		KnockForce,
		1,
		AttackStats.StunChance,
		AttackStats.StunDuration,
		ImpactSound
	);
}

void APRBaseAttack::OnAttackOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 1. Basic Validations
	if (!OtherActor || OtherActor == GetOwner() || OtherActor == this) return;
	if (!HasAuthority()) return;

	// 2. Apply Damage
	ApplyDamageToTarget(OtherActor);
}

void APRBaseAttack::HandleOverlap(AActor* OtherActor)
{
	// 1. Validations
	if (!OtherActor || OtherActor == GetOwner() || OtherActor == this) return;
	if (!HasAuthority()) return;

	if (HitHistory.Contains(OtherActor))
	{
		return;
	}

	// --- TICK RATE LOGIC ---
	// If TickRate is 0, it fires every frame (Dangerous).
	// If TickRate > 0, check it.
	if (AttackStats.TickRate > 0.0f)
	{
		double CurrentTime = GetWorld()->GetTimeSeconds();

		// Have we hit this actor before?
		if (double* LastHitTime = DamageCooldownMap.Find(OtherActor))
		{
			// If we did hit it, has enough time passed?
			if ((CurrentTime - *LastHitTime) < AttackStats.TickRate)
			{
				// The cooldown hasn't ended yet, DON'T ATTACK.
				return;
			}
		}

		// Update the list (or add a new one)
		DamageCooldownMap.Add(OtherActor, CurrentTime);
	}

	HitHistory.Add(OtherActor);

	// 2. Status Application
	HandleStatusApplication(OtherActor);

	// 3. Apply Damage
	ApplyDamageToTarget(OtherActor);

	// --- 3. BOUNCE LOGIC ---
	if (AttackStats.ProjectileBounce > 0)
	{
		if (TryBounce(OtherActor))
		{
			AttackStats.ProjectileBounce--;

			return;
		}
	}

	// --- 4. PIERCE LOGIC ---

	// If PierceCount is -1, it means infinite pierce.
	if (AttackStats.PierceCount == -1)
	{
		return;
	}

	if (AttackStats.PierceCount <= 0)
	{
		Destroy();
	}
	else
	{
		AttackStats.PierceCount--;
	}
}

bool APRBaseAttack::TryBounce(AActor* HitActor)
{
	// 1. Find Actors in Radius
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	IgnoreActors.Append(HitHistory);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Enemy)); // Only look for Enemies

	TArray<AActor*> OutActors;
	bool bFound = UKismetSystemLibrary::SphereOverlapActors(
		this,
		GetActorLocation(),
		BounceSearchRadius,
		ObjectTypes,
		APRAIBase::StaticClass(), // Only look for Enemies
		IgnoreActors,
		OutActors
	);

	if (!bFound || OutActors.Num() == 0) return false;

	// 2. Find the CLOSEST valid target
	AActor* ClosestTarget = nullptr;
	float MinDistSq = FLT_MAX;

	for (AActor* Candidate : OutActors)
	{
		if (Candidate && !Candidate->IsPendingKillPending())
		{
			// Check if alive (using StatsComponent)
			bool bIsAlive = true;
			if (APRAIBase* AI = Cast<APRAIBase>(Candidate))
			{
				if (UPRStatsComponent* Stats = AI->GetStatsComponent())
				{
					if (Stats->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health) <= 0)
						bIsAlive = false;
				}
			}

			if (bIsAlive)
			{
				float DistSq = FVector::DistSquared(GetActorLocation(), Candidate->GetActorLocation());
				if (DistSq < MinDistSq)
				{
					MinDistSq = DistSq;
					ClosestTarget = Candidate;
				}
			}
		}
	}

	// 3. Redirect the Projectile
	if (ClosestTarget)
	{
		FVector Direction = (ClosestTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();

		// Update Velocity
		if (ProjectileMovement)
		{
			float CurrentSpeed = ProjectileMovement->Velocity.Size();
			
			// If the current speed is very low, reset to default projectile speed
			if (CurrentSpeed < 500.f) CurrentSpeed = AttackStats.ProjectileSpeed;
			if (CurrentSpeed <= 0.f) CurrentSpeed = 1000.f;
			// Keep the same speed, just change direction
			ProjectileMovement->Velocity = Direction * CurrentSpeed;

			// Force update rotation
			SetActorRotation(Direction.Rotation());
		}

		DrawDebugLine(GetWorld(), GetActorLocation(), ClosestTarget->GetActorLocation(), FColor::Green, false, 1.0f, 0, 2.0f);

		return true; // Bounced!
	}

	return false; // No valid target found
}

void APRBaseAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APRBaseAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

