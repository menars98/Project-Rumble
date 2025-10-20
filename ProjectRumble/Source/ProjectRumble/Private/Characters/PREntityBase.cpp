// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PREntityBase.h"
#include "Components/PRStatsComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/PRPlayerState.h"
#include "PRGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


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
	if (DamageAmount <= 0.f)
	{
		return 0.f;
	}

	UPRStatsComponent* MyStatsComponent = GetStatsComponent();
	if (!MyStatsComponent)
	{
		return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	}

	// --- 1. EVASION ---
	if (CheckForEvasion(MyStatsComponent))
	{
		return 0.f; // Damage is completely negated.
	}

	// --- 2. SHIELD ABSORPTION ---
	// The ProcessShieldDamage function handles shield reduction and returns leftover damage.
	float DamageAfterShields = ProcessShieldDamage(DamageAmount, MyStatsComponent);
	if (DamageAfterShields <= 0.f)
	{
		// If shield absorbed all damage, we are done.
		return 0.f; // Report that 0 damage was taken by health.
	}

	// --- 3. ARMOR ---
	const float DamageToApply = CalculateArmorReduction(DamageAmount, MyStatsComponent);

	// --- APPLY DAMAGE ---
	const float ActualDamage = Super::TakeDamage(DamageToApply, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.f)
	{
		MyStatsComponent->ApplyDamage(ActualDamage);

		// --- 4. THORNS ---
		ApplyThornsDamage(MyStatsComponent, DamageCauser);
	}

	if (DamageCauser)
	{
		// Calculate the direction of the knockback: from the attacker to us.
		FVector KnockbackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockbackDirection.Z = 0; // Don't launch upwards, just backwards
		KnockbackDirection.Normalize();

		// Get a generic knockback value for now.
		// TODO: Get this value from the weapon that hit us.
		const float KnockbackMagnitude = 500.0f;

		// Launch the character!
		if (ACharacter* Char = Cast<ACharacter>(this))
		{
			Char->LaunchCharacter(KnockbackDirection * KnockbackMagnitude, true, false);
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

bool APREntityBase::CheckForEvasion(const UPRStatsComponent* StatsComponent) const
{
	const float EvasionPoints = StatsComponent->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Evasion);
	if (EvasionPoints > 0.f)
	{
		const float EvasionChance = EvasionPoints / (EvasionPoints + 100.f);
		if (FMath::FRand() < EvasionChance)
		{
			UE_LOG(LogTemp, Log, TEXT("%s EVADED the attack! (Chance: %.1f%%)"), *GetName(), EvasionChance * 100);
			// TODO: Trigger "MISS" feedback.
			return true;
		}
	}
	return false;
}

float APREntityBase::CalculateArmorReduction(float InitialDamage, const UPRStatsComponent* StatsComponent) const
{
	// 1. Get the total Armor points from the StatsComponent.
	const float ArmorPoints = StatsComponent->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Armor);

	if (ArmorPoints <= 0.f)
	{
		return InitialDamage;
	}

	// 2. Convert Armor points into a damage reduction percentage (0.0 to 1.0).
	// We use a formula to provide diminishing returns.
	// Formula: Reduction = Armor / (Armor + K). Let's use K = 200 for our prototype.
	const float K_Value = 200.0f;
	const float DamageReductionPercentage = ArmorPoints / (ArmorPoints + K_Value);

	// 3. Calculate the damage multiplier.
	// If reduction is 50% (0.5), the multiplier is 50% (0.5).
	const float DamageMultiplier = 1.0f - DamageReductionPercentage;

	// 4. Apply the multiplier to the initial damage.
	float FinalDamage = InitialDamage * DamageMultiplier;

	// Log for debugging
	UE_LOG(LogTemp, Log, TEXT("Armor Reduction: Armor Points:%.0f -> Reduction:%.1f%%. Damage: %.1f -> %.1f"),
		ArmorPoints, DamageReductionPercentage * 100, InitialDamage, FinalDamage);

	// Ensure at least 1 damage is always dealt.
	return FMath::Max(FinalDamage, 1.0f);
}

void APREntityBase::ApplyThornsDamage(const UPRStatsComponent* StatsComponent, AActor* DamageCauser)
{
	const float ThornsDamage = StatsComponent->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Thorns);
	if (ThornsDamage > 0.f && DamageCauser != this)
	{
		UGameplayStatics::ApplyDamage(DamageCauser, ThornsDamage, GetController(), this, nullptr);
	}
}

float APREntityBase::ProcessShieldDamage(float InitialDamage, UPRStatsComponent* StatsComponent)
{
	// Get current shield value
	const float CurrentShield = StatsComponent->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield);
	if (CurrentShield <= 0.f)
	{
		// No shield, so no damage is absorbed.
		return InitialDamage;
	}

	// Calculate how much damage the shield can absorb
	const float DamageAbsorbedByShield = FMath::Min(CurrentShield, InitialDamage);
	const float RemainingDamage = InitialDamage - DamageAbsorbedByShield;

	// Update the shield value
	StatsComponent->SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield, CurrentShield - DamageAbsorbedByShield);

	// Taking damage, even if it's fully absorbed by the shield, should reset the regen delay.
	StatsComponent->ResetShieldRegenDelay();

	UE_LOG(LogTemp, Log, TEXT("%s's shield absorbed %.1f damage. Remaining damage: %.1f"), *GetName(), DamageAbsorbedByShield, RemainingDamage);

	// Return the damage that was NOT absorbed.
	return RemainingDamage;
}
