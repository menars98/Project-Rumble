// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/PRBaseItem.h"
#include "Datas/PRItemDefinition.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

UPRBaseItem::UPRBaseItem()
{
	CurrentLevel = 0; // Items start at level 0 until initialized
	ItemDefinition = nullptr;
	OwningActor = nullptr;
}


void UPRBaseItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor, const TArray<FPotentialUpgradeEffect>& InitialEffects)
{
	ItemDefinition = InItemDefinition;
	OwningActor = InOwningActor;
	CurrentLevel = 1;

	UE_LOG(LogTemp, Log, TEXT("Item '%s' initialized at Level %d."), *ItemDefinition->DisplayName.ToString(), CurrentLevel);
}

void UPRBaseItem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPRBaseItem, CurrentLevel);
	DOREPLIFETIME(UPRBaseItem, ItemDefinition);
}

void UPRBaseItem::LevelUp(const TArray<FPotentialUpgradeEffect>& UpgradeEffects)
{
	CurrentLevel++;
	UE_LOG(LogTemp, Log, TEXT("Item '%s' leveled up to Level %d."), *ItemDefinition->DisplayName.ToString(), CurrentLevel);

	// Child classes will override this to add more specific logic,
	// like reapplying stat bonuses or increasing damage.
}

UWorld* UPRBaseItem::GetWorld() const
{
	if (OwningActor)
	{
		return OwningActor->GetWorld();
	}
	return nullptr;
}
