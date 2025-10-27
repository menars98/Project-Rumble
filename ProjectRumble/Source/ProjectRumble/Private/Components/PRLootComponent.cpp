// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PRLootComponent.h"
#include "Game/PRGameInstance.h"
#include "PRTypes.h"
#include "Actors/PRPickupBase.h"
#include "Engine/DataTable.h"
#include "Characters/PRCharacterBase.h"
#include "Kismet/GameplayStatics.h"

UPRLootComponent::UPRLootComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPRLootComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPRLootComponent::DropLoot()
{
	if (LootProfileTag.IsValid() == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("LootComponent on %s has no valid LootProfileTag."), *GetOwner()->GetName());
		return;
	}

	// 1. Get the global Loot Table from our GameInstance
	UPRGameInstance* GameInstance = GetWorld()->GetGameInstance<UPRGameInstance>();
	if (!GameInstance || !GameInstance->LootProfileTable)
	{
		UE_LOG(LogTemp, Error, TEXT("LootProfileTable is not set in the GameInstance!"));
		return;
	}

	// 2. Find the correct loot profile row by iterating through the table.
	FLootProfile* FoundProfile = nullptr;
	for (const FName& RowName : GameInstance->LootProfileTable->GetRowNames())
	{
		FLootProfile* Profile = GameInstance->LootProfileTable->FindRow<FLootProfile>(RowName, "");
		if (Profile && Profile->ProfileTag == LootProfileTag)
		{
			FoundProfile = Profile;
			break;
		}
	}

	if (!FoundProfile)
	{
		UE_LOG(LogTemp, Warning, TEXT("No LootProfile found in DT_LootProfiles for tag %s"), *LootProfileTag.ToString());
		return;
	}

	// 3. Roll for each possible drop in the found profile
	for (const FLootDrop& Drop : FoundProfile->PossibleDrops)
	{
		if (FMath::FRand() < Drop.DropChance)
		{
			if (Drop.PickupClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				// Set the owner of the pickup to be the actor that has this component
				SpawnParams.Owner = GetOwner();

				// Set the owner of the pickup to be the actor that has this component
				SpawnParams.Owner = GetOwner();

				// The instigator is the pawn that "owns" the owner (if the owner is an AI, for example)
				if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
				{
					SpawnParams.Instigator = OwnerPawn;
				}

				APRPickupBase* SpawnedPickup = GetWorld()->SpawnActor<APRPickupBase>(
					Drop.PickupClass,
					GetOwner()->GetActorLocation(),
					FRotator::ZeroRotator,
					SpawnParams
				);

				if (SpawnedPickup)
				{
					SpawnedPickup->Value = Drop.Value;

					// Check if this pickup type should start homing immediately.
					if (SpawnedPickup->bStartHomingOnSpawn)
					{
						// Find the player and tell the pickup to home towards them.
						if (ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
						{
							if (APRCharacterBase* Player = Cast<APRCharacterBase>(PlayerChar))
							{
								SpawnedPickup->StartHoming(Player);
							}
						}
					}
				}
			}
		}
	}
}



