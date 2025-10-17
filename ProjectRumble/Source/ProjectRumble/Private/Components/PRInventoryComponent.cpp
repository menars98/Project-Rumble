

#include "Components/PRInventoryComponent.h"
#include "Datas/PRItemDefinition.h"
#include "Datas/PRBaseItem.h"
#include "Datas/PRUpgradeData.h"
#include "GameFramework/Pawn.h" 
#include "GameFramework/PlayerState.h"

UPRInventoryComponent::UPRInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UPRInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPRInventoryComponent::AddOrUpgradeItem(UPRUpgradeData* ChosenUpgrade)
{
	if (!ChosenUpgrade) return;

    // Get the ItemDefinition from the chosen upgrade.
    UPRItemDefinition* ItemDef = ChosenUpgrade->SourceItemDefinition;

    if (!ItemDef) return; // If there is no source definition, we can't do anything.

    UPRBaseItem* ExistingItem = FindItemByDefinition(ItemDef);
    if (ExistingItem)
    {
        UpgradeExistingItem(ItemDef);
    }
    else
    {
        AddNewItem(ItemDef);
    }
}


UPRBaseItem* UPRInventoryComponent::FindItemByDefinition(const UPRItemDefinition* ItemDef) const
{
	if (!ItemDef) return nullptr;

	// Helper lambda function to search inside a given array.
	// This avoids writing the same for loop multiple times.
	auto FindInArray = [&](const TArray<TObjectPtr<UPRBaseItem>>& ItemArray) -> UPRBaseItem*
		{
			for (UPRBaseItem* Item : ItemArray)
			{
				if (Item && Item->GetItemDefinition() == ItemDef)
				{
					return Item;
				}
			}
			return nullptr;
		};

	// Now, search in all of our lists.
	if (UPRBaseItem* FoundItem = FindInArray(OwnedWeapons))
	{
		return FoundItem;
	}

	if (UPRBaseItem* FoundItem = FindInArray(OwnedTomes))
	{
		return FoundItem;
	}

	if (UPRBaseItem* FoundItem = FindInArray(OwnedRelics))
	{
		return FoundItem;
	}

	// If not found in any list, return nullptr.
	return nullptr;
}

void UPRInventoryComponent::AddNewItem(UPRItemDefinition* ItemDef)
{
	if (!ItemDef || !ItemDef->ItemClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot add new item: ItemDefinition is invalid or has no ItemClass specified."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("INVENTORY: Attempting to add new item: %s"), *ItemDef->DisplayName.ToString());

	// Create a new instance of the item's logic class (e.g., UPRWeaponItem).
	UPRBaseItem* NewItem = NewObject<UPRBaseItem>(this, ItemDef->ItemClass);
	if (NewItem)
	{
		// Get the owner of THIS component. We know it should be a PlayerState.
		APlayerState* MyOwner = GetOwner<APlayerState>();
		if (!MyOwner)
		{
			// If for some reason our owner isn't a player state, we can't find the pawn.
			// This is a safety check.
			return;
		}

		// Get the Pawn that this PlayerState controls.
		APawn* OwningPawn = MyOwner->GetPawn();

		// Initialize the item with the Pawn as its owner.
		NewItem->Initialize(ItemDef, OwningPawn);

		// Add the new item to the correct inventory list based on its type.
		switch (ItemDef->ItemType)
		{
		case EItemType::Weapon:
			if (OwnedWeapons.Num() < MaxWeapons)
			{
				OwnedWeapons.Add(NewItem);
			}
			break;
		case EItemType::Tome:
			if (OwnedTomes.Num() < MaxTomes)
			{
				OwnedTomes.Add(NewItem);
			}
			break;
		case EItemType::Relic:
			// OwnedRelics.Add(NewItem);
			break;
		}

		UE_LOG(LogTemp, Log, TEXT("Added new item '%s' to inventory."), *ItemDef->DisplayName.ToString());

		OnInventoryUpdated.Broadcast();
	}
}

void UPRInventoryComponent::UpgradeExistingItem(UPRItemDefinition* ItemDef)
{
	UPRBaseItem* ItemToUpgrade = FindItemByDefinition(ItemDef);
	if (ItemToUpgrade)
	{
		ItemToUpgrade->LevelUp();

		OnInventoryUpdated.Broadcast();
	}
}


