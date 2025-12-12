

#include "Actors/PRBaseAttack.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/PRGameplayStatics.h"
#include "Characters/PRCharacterBase.h"
#include "AI/PRAIBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

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

	ProjectileMovement->UpdatedComponent = RootCollision;
	ProjectileMovement->InitialSpeed = 0.f;
	ProjectileMovement->MaxSpeed = 0.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void APRBaseAttack::BeginPlay()
{
	Super::BeginPlay();
	
	// LifeDuration, Spawn anýnda AttackStats struct'ýndan atanacaktýr.
	SetLifeSpan(AttackStats.LifeDuration);
}

void APRBaseAttack::ApplyDamageToTarget(AActor* TargetActor)
{
    if (!HasAuthority()) return;
    if (!IsValid(TargetActor) || !IsValid(GetOwner())) return;

    // 
    float FinalDamage = AttackStats.Damage;
    FDamageCalculationResult DamageResult;
    DamageResult.FinalDamage = FinalDamage;


    AController* InstigatorController = nullptr;
    AActor* DamageCauser = GetOwner();

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
		DamageResult.bWasCriticalHit = false; // AI Crit atmasýn (veya buraya eklenebilir)
	}

	// --- Apply Damage ---
	UPRGameplayStatics::ApplyRumbleDamage(
		this,
		TargetActor,
		FinalDamage,
		DamageResult,
		InstigatorController,
		DamageCauser,
		UDamageType::StaticClass(),
		GetActorForwardVector(),
		AttackStats.KnockbackMagnitude,
		AttackStats.StunChance,
		AttackStats.StunDuration,
		ImpactSound
	);
}

void APRBaseAttack::OnAttackOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner() || OtherActor == this)
	{
		return;
	}

	ApplyDamageToTarget(OtherActor);
}

void APRBaseAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APRBaseAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

