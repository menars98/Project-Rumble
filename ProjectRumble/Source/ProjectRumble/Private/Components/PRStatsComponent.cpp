

#include "Components/PRStatsComponent.h"
#include "PRTypes.h"
#include "PRGameplayTags.h"

UPRStatsComponent::UPRStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// We turned Tick off because this component doesn't need to do anything every single frame.
	// This is a good performance optimization.
	PrimaryComponentTick.bCanEverTick = false;

}

void UPRStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStats();

	// Start the health regeneration timer loop when the component begins play.
	// The timer will call ProcessHealthRegen() every 'RegenInterval' seconds, and it will loop forever.
	GetWorld()->GetTimerManager().SetTimer(
		HealthRegenTimerHandle,
		this,
		&UPRStatsComponent::ProcessHealthRegen,
		RegenInterval,
		true 
	);

	// --- START THE SHIELD REGENERATION LOOP INITIALLY ---
	// We assume the player starts with the ability to regen shield.
	StartShieldRegen();
}

void UPRStatsComponent::InitializeStats()
{
	// Guard clause: If no data table is assigned, we can't do anything.
	if (!StatsDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("StatsComponent on %s has no StatsDataTable assigned!"), *GetOwner()->GetName());
		return;
	}

	// Get the names of all rows in the data table
	const TArray<FName> RowNames = StatsDataTable->GetRowNames();

	// Loop through each row name and find its data
	for (const FName& RowName : RowNames)
	{
		FStatDefinition* StatRow = StatsDataTable->FindRow<FStatDefinition>(RowName, TEXT("..."));

		if (StatRow)
		{
			// Use the GameplayTag from the data row as the key for our map.
			CurrentStats.Add(StatRow->StatID, StatRow->DefaultValue);

			UE_LOG(LogTemp, Log, TEXT("Initialized Stat: %s with value: %f"), *StatRow->StatID.ToString(), StatRow->DefaultValue);
		}
	}
	
	BroadcastHealth();
	BroadcastShield();
}

float UPRStatsComponent::GetStatValue(FGameplayTag StatTag) const
{
	// Find() returns a pointer to the value if the key exists in the map.
	const float* FoundValue = CurrentStats.Find(StatTag);

	if (FoundValue)
	{
		return *FoundValue;
	}

	// If the stat was not found, log a warning and return 0 as a safe default.
	UE_LOG(LogTemp, Warning, TEXT("GetStatValue: Stat '%s' not found in StatsComponent on %s."), *StatTag.ToString(), *GetOwner()->GetName());
	return 0.f;
}

void UPRStatsComponent::SetStatValue(FGameplayTag StatTag, float NewValue)
{
	// Find() here returns a pointer that we can change.
	float* FoundValue = CurrentStats.Find(StatTag);

	if (FoundValue)
	{
		*FoundValue = NewValue;

		// Broadcast that a generic stat has changed
		OnStatChangedDelegate.Broadcast(StatTag, NewValue);
		// If the stat that changed is relevant to the shield, broadcast the shield delegate.
		if (StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield || StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxShield)
		{
			BroadcastShield();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetStatValue: Stat '%s' not found in StatsComponent on %s."), *StatTag.ToString(), *GetOwner()->GetName());
	}
}

void UPRStatsComponent::ApplyDamage(float DamageAmount)
{
	// Do nothing if damage is zero or less.
	if (DamageAmount <= 0.f)
	{
		return;
	}

	const FGameplayTag HealthTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health.GetTag();
	const FGameplayTag MaxHPTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP.GetTag();

	const float CurrentHealth = GetStatValue(HealthTag);
	const float NewHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, GetStatValue(MaxHPTag));

	SetStatValue(HealthTag, NewHealth);

	// Broadcast the change to any listeners (like the Character or UI).
	BroadcastHealth();

	// Check for death
	if (NewHealth <= 0.f)
	{
		Die();
	}
}

void UPRStatsComponent::InitializeWithDataTable(UDataTable* DataTableToUse)
{
	// Check if a valid data table was provided
	if (!DataTableToUse)
	{
		UE_LOG(LogTemp, Error, TEXT("StatsComponent on %s was told to initialize with a NULL DataTable!"), *GetOwner()->GetName());
		return;
	}

	// This is the same logic as BeginPlay, but now it can be called from outside with a specific table.
	const TArray<FName> RowNames = DataTableToUse->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FStatDefinition* StatRow = DataTableToUse->FindRow<FStatDefinition>(RowName, TEXT("..."));
		if (StatRow)
		{
			// The key is now StatRow->StatID, which is an FGameplayTag.
			// The old version used RowName as the key.
			CurrentStats.Add(StatRow->StatID, StatRow->DefaultValue);
		}
	}

	BroadcastHealth();
}

void UPRStatsComponent::Die()
{
	// Broadcast the death event.
	// The owner of this component (e.g., the character) should listen to this and handle its own death logic
	// (playing animations, enabling ragdoll, etc.).
	OnDeathDelegate.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("%s has died."), *GetOwner()->GetName());
}

void UPRStatsComponent::BroadcastHealth()
{
	// Ensure the delegate is bound before broadcasting.
	if (OnHealthChangedDelegate.IsBound())
	{
		// Request the tags once for clarity. In a real project, you might store these in a central header.
		const FGameplayTag HealthTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health.GetTag();
		const FGameplayTag MaxHPTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP.GetTag();

		const float CurrentHealth = GetStatValue(HealthTag);
		const float MaxHealth = GetStatValue(MaxHPTag);
		OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth);
	}
}

void UPRStatsComponent::BroadcastShield()
{
	// Ensure the delegate is bound by at least one object before broadcasting.
	if (OnShieldChangedDelegate.IsBound())
	{
		const float CurrentShield = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield);
		const float MaxShield = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxShield);
		OnShieldChangedDelegate.Broadcast(CurrentShield, MaxShield);
	}
}

void UPRStatsComponent::AddXP(float XPAmount)
{
	if (XPAmount <= 0.f)
	{
		return;
	}
	
	// Define all the tags we'll need for this function.
	const FGameplayTag XPTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_XP.GetTag();
	const FGameplayTag MaxXPTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_MaxXP.GetTag();
	const FGameplayTag LevelTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_Level.GetTag();

	float CurrentXP = GetStatValue(XPTag);
	float MaxXP = GetStatValue(MaxXPTag);

	CurrentXP += XPAmount;

	// Check for Level Up
	while (CurrentXP >= MaxXP)
	{
		// Level Up!
		CurrentXP -= MaxXP; // Subtract the required XP and keep the remainder

		float CurrentLevel = GetStatValue(LevelTag);
		SetStatValue(LevelTag, CurrentLevel + 1);

		// Increase the XP required for the next level (e.g., by 20%)
		MaxXP *= 1.2f;
		SetStatValue(MaxXPTag, MaxXP);

		// Broadcast the level up event
		OnLevelUpDelegate.Broadcast(GetStatValue(LevelTag));
		UE_LOG(LogTemp, Warning, TEXT("LEVEL UP! New Level: %d"), (int32)GetStatValue(LevelTag));
	}

	// Update the current XP
	SetStatValue(XPTag, CurrentXP);

	// Broadcast the XP change
	OnXPChangedDelegate.Broadcast(CurrentXP, MaxXP);
}

void UPRStatsComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.f) return;

	const float CurrentHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health);
	const float MaxHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP);

	const float NewHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);

	if (NewHealth > CurrentHealth)
	{
		SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health, NewHealth);
		BroadcastHealth();
	}
}

void UPRStatsComponent::ProcessHealthRegen()
{
	const float HealthRegenPerMinute = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_HealthRegen);

	// If we have no regen stat, do nothing. This is a cheap check that runs every second.
	if (HealthRegenPerMinute <= 0.f)
	{
		return;
	}

	// 2. Convert "per minute" value to a "per second" value.
	const float HealthRegenPerSecond = HealthRegenPerMinute / 60.0f;

	// Our timer runs every "RegenInterval" seconds (which is 1.0 by default).
    // So the amount to heal in this tick is HealthRegenPerSecond * RegenInterval.
    // Since RegenInterval is 1.0, this is just HealthRegenPerSecond.
	const float HealthToRegenThisTick = HealthRegenPerSecond * RegenInterval;

	const float CurrentHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health);
	const float MaxHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP);

	// If health is already full, do nothing.
	if (CurrentHealth >= MaxHealth)
	{
		return;
	}

	// Calculate the new health, clamped to the max health.
	// The regen amount is "per second", and our timer runs every second, so no need to multiply by DeltaTime.
	const float NewHealth = FMath::Clamp(CurrentHealth + HealthToRegenThisTick, 0.f, MaxHealth);

	if (NewHealth > CurrentHealth) // Only update if there was an actual change
	{
		SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health, NewHealth);
		BroadcastHealth(); // Notify the UI
	}
}

void UPRStatsComponent::ResetShieldRegenDelay()
{
	// Stop any ongoing shield regeneration
	GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTickTimerHandle);

	// Clear any pending "start regen" timers
	GetWorld()->GetTimerManager().ClearTimer(ShieldRegenDelayTimerHandle);

	// Start a new timer that will re-enable shield regeneration after the delay
	GetWorld()->GetTimerManager().SetTimer(
		ShieldRegenDelayTimerHandle,
		this,
		&UPRStatsComponent::StartShieldRegen,
		ShieldRegenDelay,
		false // Don't loop
	);
}

void UPRStatsComponent::StartShieldRegen()
{
	// Now, start the continuous timer that will call ProcessShieldRegenTick every interval
	GetWorld()->GetTimerManager().SetTimer(
		ShieldRegenTickTimerHandle,
		this,
		&UPRStatsComponent::ProcessShieldRegenTick,
		ShieldRegenTickInterval,
		true // Loop this timer
	);
}

void UPRStatsComponent::ProcessShieldRegenTick()
{
	// Get the stats needed for regeneration
	const float ShieldRegenAmount = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_ShieldRegen); // Regen per second
	if (ShieldRegenAmount <= 0.f)
	{
		// If the player has no shield regen stat, stop the timer to save performance.
		GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTickTimerHandle);
		return;
	}

	const float CurrentShield = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield);
	const float MaxShield = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxShield);

	if (CurrentShield >= MaxShield)
	{
		// Shield is full, no need to do anything.
		return;
	}

	// Calculate how much to regenerate in this tick
	const float ShieldToRegen = ShieldRegenAmount * ShieldRegenTickInterval;
	const float NewShield = FMath::Clamp(CurrentShield + ShieldToRegen, 0.f, MaxShield);

	if (NewShield > CurrentShield)
	{
		SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield, NewShield);
	}
}
