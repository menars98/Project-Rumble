

#include "Components/PRStatsComponent.h"
#include "PRTypes.h"
#include "PRGameplayTags.h"
#include "GameModes/PRGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PRPlayerState.h"
#include "Components/PRSessionTrackerComponent.h"

UPRStatsComponent::UPRStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// We turned Tick off because this component doesn't need to do anything every single frame.
	// This is a good performance optimization.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);

}

void UPRStatsComponent::OnRep_ReplicatedStats()
{
	// Update the local cache from the replicated array
	SyncCacheFromReplicatedData();

	// Update UI
	BroadcastHealth();
	BroadcastShield();
	BroadcastXP();

	UE_LOG(LogTemp, Log, TEXT("[CLIENT] Stats replicated (%d stats received)"), ReplicatedStats.Num());
}

void UPRStatsComponent::SyncCacheFromReplicatedData()
{
	const FString OwnerName = GetOwner() ? GetOwner()->GetName() : TEXT("Unknown");
	const FString NetRole = (GetOwner() && GetOwner()->HasAuthority()) ? TEXT("SERVER") : TEXT("CLIENT");

	for (const FReplicatedStatEntry& Entry : ReplicatedStats)
	{
		// 1. Did this stat exist before, and what was its value?
		float OldValue = 0.0f;
		bool bIsNewOrChanged = false;
		//	Find the stat in the cache
		if (float* CachedValPtr = CurrentStatsCache.Find(Entry.StatTag))
		{
			OldValue = *CachedValPtr;

			if (!FMath::IsNearlyEqual(OldValue, Entry.Value))
			{
				bIsNewOrChanged = true;
				*CachedValPtr = Entry.Value;
			}
		}
		else
		{
			// New stat, add it to the cache
			bIsNewOrChanged = true;
			CurrentStatsCache.Add(Entry.StatTag, Entry.Value);
		}

		// 2. If its new or changed, broadcast the appropriate delegates
		if (bIsNewOrChanged)
		{
			UE_LOG(LogTemp, Warning, TEXT("[%s] Stat CHANGED on %s: %s | Old: %f -> New: %f"),
				*NetRole,
				*OwnerName,
				*Entry.StatTag.ToString(),
				OldValue,
				Entry.Value);
				BroadcastSingleStatChange(Entry.StatTag, Entry.Value);
		}
	}

	// If we delete stats on the server side, we would need to handle that here as well.
}

void UPRStatsComponent::SyncReplicatedDataFromCache()
{
	//Copy from Map to Array(on the server side)
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	ReplicatedStats.Empty();
	for (const TPair<FGameplayTag, float>& Pair : CurrentStatsCache)
	{
		ReplicatedStats.Add(FReplicatedStatEntry(Pair.Key, Pair.Value));
	}
}

TMap<FGameplayTag, float> UPRStatsComponent::GetCurrentStats() const
{
	return CurrentStatsCache;
}

void UPRStatsComponent::ForceUpdateUI()
{
	// Simply call the broadcast functions to update any UI or systems listening to these delegates.
	BroadcastHealth();
	BroadcastShield();
	BroadcastXP();
	BroadcastResources();
}

void UPRStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	if (StatsDataTable)
	{
		InitializeStats();
	}
	
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
			// Add the stat ID and its default value to the CurrentStats map 
			CurrentStatsCache.Add(StatRow->StatID, StatRow->DefaultValue);

			UE_LOG(LogTemp, Log, TEXT("Initialized Stat: %s with value: %f"), *StatRow->StatID.ToString(), StatRow->DefaultValue);
		}
	}
	
	// If it's a server, update the replicated array as well.
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SyncReplicatedDataFromCache();
	}

	const float CurrentHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health);
	const float MaxHealth = GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP);

	UE_LOG(LogTemp, Warning, TEXT("[%s] InitializeStats complete | Health: %.0f/%.0f | Stats Count: %d"),GetOwner()->HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"),
		CurrentHealth, MaxHealth, CurrentStatsCache.Num());
	ForceUpdateUI();
}

void UPRStatsComponent::InitializeForAI(const TArray<FStatDefinition>& BaseStatsArray, float DifficultyMultiplier)
{
	// 1. Clear any existing stats.
	CurrentStatsCache.Empty();

	// Clamp the multiplier for safety.
	if (DifficultyMultiplier < 1.0f) { DifficultyMultiplier = 1.0f; }

	bool bMaxHealthFound = false;
	float LoadedMaxHealth = 0.0f;

	// 2. Loop through the final, calculated stats provided by the AI.
	for (const FStatDefinition& StatDef : BaseStatsArray)
	{
		// 1. Calculate the scaled float value.
		float ScaledValue = StatDef.DefaultValue * DifficultyMultiplier;

		// --- 2. ROUND THE VALUE (NEW LOGIC) ---

		// Round the final value to the nearest whole number.
		// Example: 39.2f becomes 39.0f, 39.8f becomes 40.0f.
		float FinalValue = FMath::RoundToFloat(ScaledValue);

		UE_LOG(LogTemp, Warning, TEXT("AI Init: Adding Stat %s with Value %f"), *StatDef.StatID.ToString(), FinalValue);
		// Add the stat tag and the final calculated value to the runtime map.
		CurrentStatsCache.Add(StatDef.StatID, FinalValue);

		UpdateReplicatedStat(StatDef.StatID, FinalValue);
		// Check for MaxHealth to set CurrentHealth.
		if (StatDef.StatID == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP)
		{
			LoadedMaxHealth = FinalValue;
			bMaxHealthFound = true;
		}
	}

	if (GetOwner()->HasAuthority())
	{
		SyncReplicatedDataFromCache(); 
	}

	// 3. Set Current Health to Max Health.
	if (bMaxHealthFound)
	{
		SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health, LoadedMaxHealth);
	}

	// 4. Broadcast initial values to update UI or other systems.
	BroadcastHealth();
	BroadcastShield();
}

float UPRStatsComponent::GetStatValue(FGameplayTag StatTag) const
{
	// Use the cache for fast lookups.
	const float* FoundValue = CurrentStatsCache.Find(StatTag);

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
	// Only make changes on the server
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[CLIENT] Attempted to SetStatValue - ignored (must be called on server)"));
		return;
	}

	// Find() here returns a pointer that we can change.
	float* FoundValue = CurrentStatsCache.Find(StatTag);

	if (FoundValue)
	{
		*FoundValue = NewValue;

		// Update the replicated array to reflect the change.
		UpdateReplicatedStat(StatTag, NewValue);

		// Broadcast that a generic stat has changed
		OnStatChangedDelegate.Broadcast(StatTag, NewValue);

		BroadcastSingleStatChange(StatTag, NewValue);
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
			CurrentStatsCache.Add(StatRow->StatID, StatRow->DefaultValue);
		}
	}

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		SyncReplicatedDataFromCache();
	}
	BroadcastHealth();
}

void UPRStatsComponent::Die()
{
	ShutdownStats();
	// Broadcast the death event.
	// The owner of this component (e.g., the character) should listen to this and handle its own death logic
	// (playing animations, enabling ragdoll, etc.).
	OnDeathDelegate.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("%s has died."), *GetOwner()->GetName());
}

void UPRStatsComponent::UpdateReplicatedStat(FGameplayTag StatTag, float NewValue)
{
	// Only run on server
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}

	// 1. Try to find the existing stat in the array and update it.
	for (FReplicatedStatEntry& Entry : ReplicatedStats)
	{
		if (Entry.StatTag == StatTag)
		{
			// Found it! Update value and stop.
			// Since we modify the value inside the array, Unreal's replication system 
			// will detect ONLY this change and send a small packet.
			Entry.Value = NewValue;
			return;
		}
	}

	// 2. If we are here, the stat doesn't exist in the array yet. Add it.
	ReplicatedStats.Add(FReplicatedStatEntry(StatTag, NewValue));
}

void UPRStatsComponent::BroadcastHealth()
{
	const FGameplayTag HealthTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health.GetTag();
	const FGameplayTag MaxHPTag = NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP.GetTag();

	const float CurrentHealth = GetStatValue(HealthTag);
	const float MaxHealth = GetStatValue(MaxHPTag);

	if (OnHealthChangedDelegate.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("Broadcasting Health Update: %.1f / %.1f (Listeners Bound)"), CurrentHealth, MaxHealth);
		OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BroadcastHealth called but NO LISTENERS BOUND! HP: %.1f / %.1f"), CurrentHealth, MaxHealth);
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

void UPRStatsComponent::BroadcastXP()
{
	if(OnXPChangedDelegate.IsBound())
	{
		const float CurrentXP = GetStatValue(NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_XP);
		const float MaxXP = GetStatValue(NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_MaxXP);
		UE_LOG(LogTemp, Warning, TEXT("STATS: Broadcasting XP Change. Current: %f, Max: %f"), CurrentXP, MaxXP);
		OnXPChangedDelegate.Broadcast(CurrentXP, MaxXP);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("STATS: XP Changed but NO ONE is listening! (Delegate not bound)"));
	}
}

void UPRStatsComponent::BroadcastResources()
{
	if (!OnResourceChangedDelegate.IsBound())
	{
		return;
	}

	// Define the parent tag for resources
	const FGameplayTag ResourceParentTag = FGameplayTag::RequestGameplayTag(FName("Stat.Resource"));

	for (const TPair<FGameplayTag, float>& Pair : CurrentStatsCache)
	{
		// Check if the stat tag matches the Resource parent tag
		if (Pair.Key.MatchesTag(ResourceParentTag))
		{
			int32 ResourceAmount = FMath::RoundToInt(Pair.Value);

			OnResourceChangedDelegate.Broadcast(Pair.Key, ResourceAmount);
		}
	}
}

void UPRStatsComponent::BroadcastSingleStatChange(const FGameplayTag& StatTag, float NewValue)
{
	// 1. Generic Stat Change
	if (OnStatChangedDelegate.IsBound())
	{
		OnStatChangedDelegate.Broadcast(StatTag, NewValue);
	}

	// 2. Resource Control
	if (StatTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Stat.Resource"))))
	{
		if (OnResourceChangedDelegate.IsBound())
		{
			OnResourceChangedDelegate.Broadcast(StatTag, FMath::RoundToInt(NewValue));
		}
	}

	// 3. Difficulty Control
	if (StatTag == NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Difficulty)
	{
		if (OnDifficultyChangedDelegate.IsBound())
		{
			OnDifficultyChangedDelegate.Broadcast(NewValue);
		}
	}

	// 4. Health Control 
	if (StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health ||
		StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxHP)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health/MaxHP Change Detected! Calling BroadcastHealth..."));

		BroadcastHealth();
	}

	// 5. Shield Control
	if (StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Shield ||
		StatTag == NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_MaxShield)
	{
		BroadcastShield();
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
	BroadcastXP();
}

void UPRStatsComponent::ShutdownStats()
{
	// Clear all timers related to stats
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
		World->GetTimerManager().ClearTimer(ShieldRegenDelayTimerHandle);
		World->GetTimerManager().ClearTimer(ShieldRegenTickTimerHandle);
	}

	UE_LOG(LogTemp, Log, TEXT("Stats Component Shutdown for %s"), *GetOwner()->GetName());
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
		float AmountHealed = NewHealth - CurrentHealth;

		SetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health, NewHealth);
		BroadcastHealth(); // Notify the UI

		if (APRPlayerState* PS = Cast<APRPlayerState>(GetOwner())) // Owner PlayerState ise (Veya karakterden PS'ye ulaþ)
		{
			// Not: StatsComponent PlayerState üzerinde duruyor olabilir, direkt Owner'a cast et.
			if (PS->TrackerComponent)
			{
				PS->TrackerComponent->AddStat(NativeGameplayTags::Tracker::TAG_Tracker_Survival_Health_Healing_Regen, AmountHealed);
			}
		}
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

void UPRStatsComponent::RefreshCurrentStats()
{
	if (OnStatChangedDelegate.IsBound())
	{
		for (const TPair<FGameplayTag, float>& Pair : CurrentStatsCache)
		{
			OnStatChangedDelegate.Broadcast(Pair.Key, Pair.Value);
		}
	}

	BroadcastHealth();
	BroadcastShield();
	BroadcastXP();
	BroadcastResources();

	UE_LOG(LogTemp, Log, TEXT("Refreshed all stats for %s. Processed %d entries."), *GetOwner()->GetName(), CurrentStatsCache.Num());
}

void UPRStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPRStatsComponent, ReplicatedStats);
}
