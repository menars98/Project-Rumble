

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

	const FGameplayTag HealthTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_Health.GetTag();
	const FGameplayTag MaxHPTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_MaxHP.GetTag();

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
		const FGameplayTag HealthTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_Health.GetTag();
		const FGameplayTag MaxHPTag = NativeGameplayTags::Stats::Primary::TAG_Stat_Primary_MaxHP.GetTag();

		const float CurrentHealth = GetStatValue(HealthTag);
		const float MaxHealth = GetStatValue(MaxHPTag);
		OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth);
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