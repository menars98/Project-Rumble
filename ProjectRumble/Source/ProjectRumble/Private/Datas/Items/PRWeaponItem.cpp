// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/Items/PRWeaponItem.h"
#include "Characters/PRCharacterBase.h"
#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "Datas/PRItemDefinition.h"
#include "Datas/PRWeaponDefinition.h"
#include "PRGameplayTags.h"
#include "TimerManager.h" 
#include "Net/UnrealNetwork.h"
#include <Game/PRGameState.h>

void UPRWeaponItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects)
{
	Super::Initialize(InItemDefinition, InOwningActor, InitialEffects);

	// Store and apply the initial effects for this weapon
	AppliedEffects = InitialEffects;
	RecalculateLocalStats();

	// Cache the weapon definition for easy access later
	CachedWeaponDef = Cast<UPRWeaponDefinition>(InItemDefinition);

	if (OwningActor && OwningActor->HasAuthority())
	{
		if (UWorld* World = GetWorld())
		{
			if (APRGameState* GS = World->GetGameState<APRGameState>())
			{
				// CASE 1: The game has already started (e.g., you leveled up, you got a new weapon)
				if (GS->IsGameActive())
				{
					Attack();
				}
				// CASE 2: The game has not started yet (Lobby or Loading)
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Weapon %s waiting for Game Start..."), *GetName());

					// Subscribe to the event. When the game starts, “HandleGameStarted” will run.
					GS->OnGameStarted.AddDynamic(this, &UPRWeaponItem::HandleGameStarted);
				}
			}
		}
	}
}

void UPRWeaponItem::LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects)
{
	Super::LevelUp(UpgradeEffects);

	if (!ItemDefinition) return;

	// Add the new upgrade effects to our total list
	AppliedEffects.Append(UpgradeEffects);

	// Apply ONLY the new bonuses from this level up
	RecalculateLocalStats();

	// When the weapon levels up, its stats (like cooldown) might change.
	// We need to restart the timer with the new calculated cooldown.
	if (OwningActor && OwningActor->HasAuthority() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		Attack();
	}

	// Check if we reached a milestone level.
	for (const FLevelMilestone& Milestone : this->Milestones)
	{
		if (Milestone.LevelRequired == CurrentLevel)
		{
			// We reached a milestone! Grant the tag.
			AcquiredAbilityTags.AddTag(Milestone.TagToGrant);
			UE_LOG(LogTemp, Warning, TEXT("Item %s reached Level %d and gained ability tag: %s"),
				*ItemDefinition->DisplayName.ToString(), CurrentLevel, *Milestone.TagToGrant.ToString());
		}
	}

}

void UPRWeaponItem::Attack()
{
	if (!OwningActor) return;

	if (!OwningActor->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[CLIENT] Attack blocked - not authority"));
		return;
	}

	// Get the actual class name of this object instance and print it.
	FString ClassName = GetClass()->GetName();
	UE_LOG(LogTemp, Error, TEXT("ATTACKING WITH CLASS: %s"), *ClassName);

	// Perform the attack logic defined in the Blueprint.
	ExecuteAttack();

	// Set the timer to call this function again after the cooldown.
	const float Cooldown = GetCalculatedCooldown();
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &UPRWeaponItem::Attack, Cooldown, false);
}

void UPRWeaponItem::HandleGameStarted()
{
	// Now the game has started, we can go on the offensive.
	UE_LOG(LogTemp, Warning, TEXT("Weapon %s starting attack via GameStart Event!"), *GetName());

	// Let's exit the event (Clean up, don't call it again)
	if (UWorld* World = GetWorld())
	{
		if (APRGameState* GS = World->GetGameState<APRGameState>())
		{
			GS->OnGameStarted.RemoveDynamic(this, &UPRWeaponItem::HandleGameStarted);
		}
	}

	Attack();
}

float UPRWeaponItem::GetCalculatedCooldown() const
{
	// CachedWeaponDef kullanýyoruz (Cast maliyeti yok)
	if (!CachedWeaponDef) return 1.0f;

	float BaseCooldown = CachedWeaponDef->WeaponStats.BaseCooldown;

	// --- 1. Calculate Speed ---
	float TotalSpeed = GetTotalSpeedMultiplier();

	// --- 2.  (Diminishing Returns) ---
	// %500 Hýz yapýnca cooldown 0 olmasýn diye "Üs" alýyoruz.
	// 0.8f iyi bir dengedir.
	float EffectiveSpeed = FMath::Pow(TotalSpeed, 0.8f);

	// --- 3. DÜZ AZALTMA (Varsa) ---
	float FlatReduction = 0.0f;
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			FlatReduction = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Additive);
		}
	}

	// --- 4. Formula ---
	float FinalCooldown = (BaseCooldown - FlatReduction) / EffectiveSpeed;

	// Hard Cap: En hýzlý 0.1 saniyede bir ateþ etsin (10 FPS korumasý)
	return FMath::Max(FinalCooldown, 0.1f);
}

float UPRWeaponItem::GetCalculatedDamage() const
{
	if (!ItemDefinition) return 0.f;

	// 1. Get the weapon's own base damage
	float BaseDamage = CachedWeaponDef->WeaponStats.BaseDamage;

	// 1.a Get any local stat modifiers from this weapon item instance
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Additive);
	// TODO: Add damage scaling from the weapon's own level. This could also be an additive bonus.

	//2. Get global modifiers from the player
	float GlobalBonus = 0.0f;
	float GlobalMulti = 1.0f;

	// 2. Get all modifiers from the player's StatsComponent
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Additive);
			// Multiplicative bonuses are added together (e.g., 0.1 + 0.05 = 0.15 for +15%)
			GlobalMulti = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Multiplicative);
		}
	}

	// 3. Calculate the final damage
	// FORMULA: (Base + Additive) * Multiplicative
	return (BaseDamage + LocalBonus + GlobalBonus) * GlobalMulti;
}

float UPRWeaponItem::GetCalculatedCritChance() const
{
	if (!ItemDefinition) return 0.f;
	float BaseChance = CachedWeaponDef->WeaponStats.BaseCritChance;
	
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
		
	float GlobalBonus = 0.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
		}
	}
	
	float FinalCritChance = (BaseChance + LocalBonus + GlobalBonus);

	// FORMULA: Base + Additive, @TODO: Maybe we dont have to clamp? We can take surplus chance and increase crit damage?
	return FMath::Clamp(FinalCritChance, 0.f, 1.f); // Clamp to 0-1 range (0% to 100%)
}

float UPRWeaponItem::GetCalculatedCritDamage() const
{
	if (!ItemDefinition) return 2.0f; // Return a safe default if no definition

	// Base critical damage multiplier is always 2.0x (200%)
	float BaseMult = 2.0f; // Standard 200%
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);
	float GlobalBonus = 1.0f;

	// 2. Get the additional critical damage bonus from the player's global stats.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// The CritDamage stat is an additive bonus on top of the base multiplier.
			// e.g., Base 2 + 0.5 from items = 2.5x total multiplier.
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);
		}
	}

	return BaseMult + LocalBonus + GlobalBonus;
}

float UPRWeaponItem::GetCalculatedSize() const
{
	if (!ItemDefinition || !OwningActor) return 1.0f;

	float BaseSize = CachedWeaponDef->WeaponStats.BaseSize;

	// Size is usually a multiplier (1.0 base). 
	// Bonuses are additive to the multiplier (e.g. +0.5 means 1.5x size).
	float LocalSizeBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Size);
	float GlobalSizeBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Size.Multiplicative"
			GlobalSizeBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Size);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseSize * (LocalSizeBonus + GlobalSizeBonus);
}

float UPRWeaponItem::GetCalculatedKnockback() const
{
	if (!ItemDefinition || !OwningActor) return 0.f;

	float BaseKnockback = CachedWeaponDef->WeaponStats.BaseKnockback;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Physics::TAG_Stat_Physics_Knockback);
	float GlobalBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Knockback.Multiplicative"
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Physics::TAG_Stat_Physics_Knockback);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseKnockback * (LocalBonus + GlobalBonus);
}

float UPRWeaponItem::GetCalculatedDuration() const
{
	if (!ItemDefinition || !OwningActor) return 0.f;

	float BaseDuration = CachedWeaponDef->WeaponStats.BaseDuration;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Duration);
	float GlobalBonus = 1.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming the tag is "Stat.Weapon.Duration.Multiplicative"
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Duration);
		}
	}

	// FORMULA: Base * Multiplicative
	return BaseDuration * (LocalBonus + GlobalBonus);
}

// @TODO Change it to float because we keep count number float but cast to int32 when spawning projectiles
int32 UPRWeaponItem::GetCalculatedProjectileBounce() const
{
	if (!ItemDefinition || !OwningActor) return 0;

	int32 BaseBounce = CachedWeaponDef->WeaponStats.BaseProjectileBounce;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileBounce);
	float GlobalBonus = 0.0f;

	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = static_cast<int32>(StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileBounce));
		}
	}

	// FORMULA: Base + Additive
	return BaseBounce + static_cast<int32>(LocalBonus) + static_cast<int32>(GlobalBonus);
}

// @TODO Change it to float because we keep count number float but cast to int32 when spawning projectiles
int32 UPRWeaponItem::GetCalculatedProjectileCount() const
{
	if (!ItemDefinition || !OwningActor) return 1;

	int32 BaseCount = CachedWeaponDef->WeaponStats.BaseProjectileCount;
	
	// Retrieve as float, cast to int
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileCount);
	float GlobalBonus = 0.0f;

	// @TODO: Maybe Add scaling per level from the item itself (e.g., at level 5, BaseCount becomes 2)

	// 2. Get the additive bonus from the player's global stats
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileCount);
		}
	}

	// Final count is the base + bonus
	return BaseCount + static_cast<int32>(LocalBonus) + static_cast<int32>(GlobalBonus);
}

int32 UPRWeaponItem::GetCalculatedPierceCount() const
{
	if (!ItemDefinition || !OwningActor) return 1;

	// 1. Base Pierce
	int32 BasePierce = CachedWeaponDef->WeaponStats.BasePierceCount;

	// 2. Local Bonus (Weapon Upgrades)
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_PierceCount);

	// 3. Global Bonus (Player Stats)
	float GlobalBonus = 0.0f;
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_PierceCount);
		}
	}

	// Final Pierce = Base + Local + Global
	return BasePierce + FMath::RoundToInt(LocalBonus + GlobalBonus);
}

float UPRWeaponItem::GetCalculatedProjectileSpeed() const
{
	if (!ItemDefinition) return 0.f;

	// 1. Get the base projectile speed from the weapon's definition
	float BaseSpeed = CachedWeaponDef->WeaponStats.BaseProjectileSpeed;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileSpeed);
	float GlobalBonus = 1.0f;

	// 2. Get the multiplicative speed bonus from the player's global stats
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_ProjectileSpeed);
		}
	}

	// Formula: Base * (Local + Global)
	// Assuming speed bonuses are multipliers (e.g. +0.1 = 10% faster)
	return BaseSpeed * (LocalBonus + GlobalBonus);;
}

float UPRWeaponItem::GetCalculatedStunChance() const
{
	if (!ItemDefinition) return 0.0f;

	// 1. Get the weapon's base stun chance (e.g., a heavy mace might have a high base chance).
	// This value should be in the 0-1 range.
	float BaseChance = CachedWeaponDef->WeaponStats.BaseStunChance;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunChance);
	float GlobalBonus = 0.0f;

	// 2. Get the additive bonus from the player's global stats.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Player's bonus is also additive (e.g., 0.1 for +10% chance).
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunChance);
		}
	}

	// Clamp the final chance between 0% and 100%.
	return FMath::Clamp(BaseChance + LocalBonus + GlobalBonus, 0.f, 1.f);
}

float UPRWeaponItem::GetCalculatedStunDuration() const
{
	if (!ItemDefinition) return 0.0f;

	// 1. Get the weapon's base stun duration.
	float BaseDuration = CachedWeaponDef->WeaponStats.BaseStunDuration;
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunDuration);
	float GlobalBonus = 1.0f;

	// 2. Get the multiplicative bonus from the player's global stats.
	// Duration is often multiplicative.
	if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
	{
		if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
		{
			// Assuming you have a "Stat.Effect.StunDuration.Multiplicative" tag.
			// Let's use a single tag for simplicity for now.
			GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::StatusEffect::TAG_Stat_Effect_StunDuration);
		}
	}

	return BaseDuration * (LocalBonus + GlobalBonus);
}

float UPRWeaponItem::GetTotalSpeedMultiplier() const
{
	// 1. Local Bonus (From Weapon)
	float LocalBonus = LocalStatModifiers.FindRef(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Multiplicative);

	// 2. Global Bonus (From Character)
	float GlobalBonus = 1.0f;
	if (OwningActor)
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
			if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
			{
				GlobalBonus = StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_AttackSpeed_Multiplicative);
			}
		}
	}

	//Bonuses
	float TotalSpeed = LocalBonus + GlobalBonus;

	// Hard Cap
	return FMath::Max(0.1f, TotalSpeed);
}

float UPRWeaponItem::GetCalculatedTickRate() const
{
	 if (!CachedWeaponDef) return 0.0f;

    float BaseTick = CachedWeaponDef->WeaponStats.BaseTickRate;

    // If the Tick Rate is 0 (single-shot bullet), do not perform the calculation.
    if (BaseTick <= 0.0f) return 0.0f;

	// --- CRITICAL CONTROL ---
	// Should this weapon's Tick Rate be accelerated with Attack Speed?
	// Axe/Rock -> FALSE (Remains constant)
	// Aura/Puddle -> TRUE (Accelerates)
    if (CachedWeaponDef->WeaponStats.bScaleTickWithAttackSpeed)
    {
        float SpeedMult = GetTotalSpeedMultiplier();
        
		// We may not apply diminishing returns to Aura; let the player feel empowered as they grow stronger.
		// Formula: Base / Speed (If Speed is 2x, the duration is halved)
        float ScaledTick = BaseTick / SpeedMult;

        return FMath::Max(ScaledTick, 0.1f); // En hýzlý 0.1s
    }

	// If there is no scale, return the base value directly
    return BaseTick;
}

FDamageCalculationResult UPRWeaponItem::CalculateFinalDamage(const APRAIBase* Target)
{
	FDamageCalculationResult Result;
	if (!OwningActor || !Target) return Result;

	// Start with the weapon's calculated base damage
	Result.FinalDamage = GetCalculatedDamage();

	// --- CRIT CHANCE & CRIT DAMAGE LOGIC ---
	const float CritChance = GetCalculatedCritChance();
	if (FMath::FRand() < CritChance)
	{
		Result.bWasCriticalHit = true;
		const float CritDamageMultiplier = GetCalculatedCritDamage(); // Needs a new GetCalculated... function
		Result.FinalDamage *= CritDamageMultiplier;
	}

	// --- DAMAGE TO ELITES & BOSSES LOGIC ---
	if (Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Elite) || Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Boss))
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
			if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
			{
				const float EliteDamageBonus = 1.0f + StatsComp->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Elites);
				Result.FinalDamage *= EliteDamageBonus;
			}
		}
	}

	return Result;
}

//void UPRWeaponItem::ApplyBonuses(const TArray<FPotentialUpgradeEffect>& EffectsToApply)
//{
//	if (!OwningActor) return;
//
//	APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor);
//	if (!Player) return;
//
//	UPRStatsComponent* StatsComp = Player->GetStatsComponent();
//	if (!StatsComp) return;
//
//	 for (const FPotentialUpgradeEffect& Effect : EffectsToApply)
//    {
//		 // Find the current local modifier for the target stat, or add it if it doesn't exist
//        float& CurrentLocalValue = LocalStatModifiers.FindOrAdd(Effect.TargetStat);
//
//		// Add the new bonus to the local modifier
//        CurrentLocalValue += Effect.BaseMinMagnitude;
//
//        UE_LOG(LogTemp, Log, TEXT("WEAPON LOCAL UPGRADE: %s gained %f on %s"), *GetName(), Effect.BaseMinMagnitude, *Effect.TargetStat.ToString());
//    }
//}

void UPRWeaponItem::OnRep_AppliedEffects()
{
	// New effects have arrived for the client!
	// We need to update the map.
	RecalculateLocalStats();
}

void UPRWeaponItem::RecalculateLocalStats()
{
	// 1. Clean Map
	LocalStatModifiers.Empty();

	// 2. Reapply all effects
	for (const FPotentialUpgradeEffect& Effect : AppliedEffects)
	{
		float& CurrentValue = LocalStatModifiers.FindOrAdd(Effect.TargetStat);
		CurrentValue += Effect.BaseMinMagnitude;
	}

	// UE_LOG(LogTemp, Log, TEXT("Weapon Local Stats Recalculated."));
}

FPRWeaponAttackStats UPRWeaponItem::GetCalculatedAttackStats() const
{
	FPRWeaponAttackStats FinalStats;

	if (!CachedWeaponDef) return FinalStats;

	FinalStats.Damage = GetCalculatedDamage();
	FinalStats.AttackSpeed = GetCalculatedCooldown();
	FinalStats.CritChance = GetCalculatedCritChance();
	FinalStats.CritMultiplier = GetCalculatedCritDamage();
	FinalStats.SizeMultiplier = GetCalculatedSize();
	FinalStats.KnockbackMagnitude = GetCalculatedKnockback();
	FinalStats.StunChance = GetCalculatedStunChance();
	FinalStats.StunDuration = GetCalculatedStunDuration();
	FinalStats.LifeDuration = GetCalculatedDuration();
	FinalStats.ProjectileCount = GetCalculatedProjectileCount();
	FinalStats.ProjectileSpeed = GetCalculatedProjectileSpeed();
	FinalStats.ProjectileBounce = GetCalculatedProjectileBounce();
	FinalStats.PierceCount = GetCalculatedPierceCount();
	FinalStats.TickRate = GetCalculatedTickRate();
	FinalStats.StatusEffects = CachedWeaponDef->WeaponStats.AppliedStatuses;

	// --- GLOBAL IMBUES ---
	if (OwningActor)
	{
		if (APRCharacterBase* Player = Cast<APRCharacterBase>(OwningActor))
		{
			if (UPRStatsComponent* StatsComp = Player->GetStatsComponent())
			{
				// 1. Poison Imbue Control
				float GlobalImbue = StatsComp->GetStatValue(NativeGameplayTags::Status::TAG_Status_Imbue_Poison);
				float LocalImbue = LocalStatModifiers.FindRef(NativeGameplayTags::Status::TAG_Status_Imbue_Poison);

				float TotalPoison = LocalImbue + GlobalImbue;

				if (TotalPoison > 0.0f)
				{
					// Create a new status effect entry for Poison
					FStatusApplicationData NewStatus;
					NewStatus.StatusTag = NativeGameplayTags::Status::TAG_Status_Poison_PoisonStacks;
					NewStatus.StackAmount = FMath::RoundToInt(TotalPoison);

					// Add it to the final stats
					FinalStats.StatusEffects.Add(NewStatus);
				}

				// @TODO: Add other imbues like Fire, Ice, etc. here as needed. 
			}
		}
		// Note: TickRate (for DOT) must come from ItemDefinition.
		//For example, FinalStats.TickRate = ItemDefinition->WeaponStats.BaseTickRate;
	}
	return FinalStats;
}

void UPRWeaponItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPRWeaponItem, AppliedEffects);
}

void UPRWeaponItem::Deactivate()
{
	Super::Deactivate();

	if (UWorld* World = GetWorld())
	{
		// 1. Stop timer
		World->GetTimerManager().ClearTimer(AttackTimerHandle);
	}

	// 2. Clear any active effects like Aura
	// If the weapon spawned an Aura (Actor) and we are holding a reference to it, we must also destroy it.
	// Example: if (SpawnedAuraActor) SpawnedAuraActor->Destroy();
}


