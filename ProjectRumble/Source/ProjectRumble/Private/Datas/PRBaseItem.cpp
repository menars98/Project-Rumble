// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/PRBaseItem.h"
#include "Datas/PRItemDefinition.h"

UPRBaseItem::UPRBaseItem()
{
	CurrentLevel = 0; // Items start at level 0 until initialized
	ItemDefinition = nullptr;
	OwningActor = nullptr;
}

void UPRBaseItem::Initialize(UPRItemDefinition* InItemDefinition, AActor* InOwningActor)
{
	ItemDefinition = InItemDefinition;
	OwningActor = InOwningActor;
	CurrentLevel = 1; // When an item is first acquired, it's Level 1.

	UE_LOG(LogTemp, Log, TEXT("Item '%s' initialized at Level %d."), *ItemDefinition->DisplayName.ToString(), CurrentLevel);
}

void UPRBaseItem::LevelUp()
{
	CurrentLevel++;
	UE_LOG(LogTemp, Log, TEXT("Item '%s' leveled up to Level %d."), *ItemDefinition->DisplayName.ToString(), CurrentLevel);

	// Child classes will override this to add more specific logic,
	// like reapplying stat bonuses or increasing damage.
}
