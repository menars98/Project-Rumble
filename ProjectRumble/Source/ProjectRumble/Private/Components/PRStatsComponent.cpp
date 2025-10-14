

#include "Components/PRStatsComponent.h"
#include <PRTypes.h>

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
		// FindRow is a function that looks up a row by its name.
		// The second parameter is a "context string" for error messages.
		FStatDefinition* StatRow = StatsDataTable->FindRow<FStatDefinition>(RowName, TEXT("StatsComponent InitializeStats"));

		if (StatRow)
		{
			// Add the stat and its default value to our runtime map.
			CurrentStats.Add(RowName, StatRow->DefaultValue);
			UE_LOG(LogTemp, Log, TEXT("Initialized Stat: %s with value: %f"), *RowName.ToString(), StatRow->DefaultValue);
		}
	}

	// After initializing all stats, broadcast the initial health so the UI can be updated.
	BroadcastHealth();
}

float UPRStatsComponent::GetStatValue(FName StatID) const
{
	// Find() returns a pointer to the value if the key exists in the map.
	const float* FoundValue = CurrentStats.Find(StatID);

	if (FoundValue)
	{
		return *FoundValue;
	}

	// If the stat was not found, log a warning and return 0 as a safe default.
	UE_LOG(LogTemp, Warning, TEXT("GetStatValue: Stat '%s' not found in StatsComponent on %s."), *StatID.ToString(), *GetOwner()->GetName());
	return 0.f;
}

void UPRStatsComponent::SetStatValue(FName StatID, float NewValue)
{
	// Find() here returns a pointer that we can change.
	float* FoundValue = CurrentStats.Find(StatID);

	if (FoundValue)
	{
		*FoundValue = NewValue;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SetStatValue: Stat '%s' not found in StatsComponent on %s."), *StatID.ToString(), *GetOwner()->GetName());
	}
}

void UPRStatsComponent::ApplyDamage(float DamageAmount)
{
	// Do nothing if damage is zero or less.
	if (DamageAmount <= 0.f)
	{
		return;
	}

	const float CurrentHealth = GetStatValue(FName("Health"));
	const float NewHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, GetStatValue(FName("MaxHealth")));

	SetStatValue(FName("Health"), NewHealth);

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
		FStatDefinition* StatRow = DataTableToUse->FindRow<FStatDefinition>(RowName, TEXT("StatsComponent InitializeWithDataTable"));
		if (StatRow)
		{
			CurrentStats.Add(RowName, StatRow->DefaultValue);
		}
	}

	BroadcastHealth(); // Broadcast initial health after setup
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
	// Ensure the delegate is bound by at least one object before broadcasting to avoid issues.
	if (OnHealthChangedDelegate.IsBound())
	{
		const float CurrentHealth = GetStatValue(FName("Health"));
		const float MaxHealth = GetStatValue(FName("MaxHealth"));
		OnHealthChangedDelegate.Broadcast(CurrentHealth, MaxHealth);
	}
}