// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PRDestructibleProp.h"
#include "Components/PRStatsComponent.h"
#include "Components/PRLootComponent.h"
#include "PRGameplayTags.h"

APRDestructibleProp::APRDestructibleProp()
{
	PrimaryActorTick.bCanEverTick = false; 
	bReplicates = true; 

	// 1. Mesh (Root)
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	// For projectiles to interact with destructible props, set collision profile to BlockAllDynamic
	// @TODO: Create a custom collision profile for destructible props
	MeshComp->SetCollisionProfileName(FName("BlockAllDynamic"));

	// 2. Stats
	StatsComp = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComp"));

	// 3. Loot
	LootComp = CreateDefaultSubobject<UPRLootComponent>(TEXT("LootComp"));

}

void APRDestructibleProp::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		// We set the health to 1 directly for destructible props.
		if (StatsComp)
		{
			StatsComp->SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health, 1.0f);
			StatsComp->SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP, 1.0f);

			// Knockback Resistance 1.0
			StatsComp->SetStatValue(NativeGameplayTags::Stats::Physics::TAG_Stat_Defense_KnockbackResistance, 1.0f);

			// Bind to OnDeath event
			StatsComp->OnDeathDelegate.AddDynamic(this, &APRDestructibleProp::OnPropDestroyed);
		}
	}
	
}

void APRDestructibleProp::OnPropDestroyed()
{
	// 1. Drop
	if (LootComp)
	{
		LootComp->DropLoot();
	}

	// 2. Visual Effects (TODO)
	// We should create blueprintable event for VFX/SFX

	Destroy();
}

float APRDestructibleProp::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!HasAuthority() || DamageAmount <= 0.f) return 0.f;

	// We dont need complex damage handling for destructible props.

	if (StatsComp)
	{
		StatsComp->ApplyDamage(DamageAmount);
	}

	return DamageAmount;
}

void APRDestructibleProp::ReactToDamage_Implementation(float DamageAmount)
{
}

