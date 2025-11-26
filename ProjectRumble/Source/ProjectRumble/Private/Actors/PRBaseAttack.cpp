

#include "Actors/PRBaseAttack.h"
#include "Components/SphereComponent.h"
#include "FunctionLibrary/PRGameplayStatics.h"
#include "Characters/PRCharacterBase.h"
#include "AI/PRAIBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

APRBaseAttack::APRBaseAttack()
{
	PrimaryActorTick.bCanEverTick = false;

	// Setup the default lifespan
	InitialLifeSpan = AttackStats.LifeDuration; 

    AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComp->SetupAttachment(RootCollision);
    AudioComp->bAutoActivate = false;
}

void APRBaseAttack::BeginPlay()
{
	Super::BeginPlay();
	
	// LifeDuration, Spawn anýnda AttackStats struct'ýndan atanacaktýr.
	SetLifeSpan(AttackStats.LifeDuration);
}

void APRBaseAttack::ApplyDamageToTarget(AActor* TargetActor)
{
    if (ImpactSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
    }

    // Ensure all necessary actors are valid.
    if (!IsValid(TargetActor) || !IsValid(GetOwner()))
    {
        return;
    }

    // 1. Get Required Components/Actors

    // Owner is the Player Character, which is the actual damage dealer.
    APRCharacterBase* PlayerCharacter = Cast<APRCharacterBase>(GetOwner());
    if (!PlayerCharacter)
    {
        return;
    }

    // Get the Stats Component from the Player Character.
    UPRStatsComponent* AttackerStats = PlayerCharacter->GetStatsComponent();
    if (!AttackerStats)
    {
        return;
    }

    // Get Instigator Controller (The Controller of the Owner/Player).
    AController* InstigatorController = PlayerCharacter->GetController();
    AActor* DamageCauser = GetOwner(); // The actual character dealing the damage.

    // Get the target as a Base AI to pass to the damage calculator.
    const APRAIBase* TargetAI = Cast<APRAIBase>(TargetActor);

    // 2. Calculate Final Damage using the UPRGameplayStatics Helper
    // We pass the base stats from the AttackStats struct.
    FDamageCalculationResult DamageResult = UPRGameplayStatics::CalculateFinalDamage(
        AttackerStats,
        AttackStats.Damage,           // Base Damage from the struct
        AttackStats.CritChance,       // Base Crit Chance from the struct
        AttackStats.CritMultiplier,   // Base Crit Multiplier from the struct
        TargetAI
    );

    // 3. Apply Damage

    // Call the central damage application function.
    UPRGameplayStatics::ApplyRumbleDamage(
        this, // WorldContextObject (The Projectile Actor itself)
        TargetActor,
        AttackStats.Damage, 
        DamageResult,             
        InstigatorController,
        DamageCauser,
        UDamageType::StaticClass(),
        GetActorForwardVector(), // Knockback Direction (Can be changed in BP if needed)
        AttackStats.KnockbackMagnitude,
        AttackStats.StunChance,
        AttackStats.StunDuration
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

