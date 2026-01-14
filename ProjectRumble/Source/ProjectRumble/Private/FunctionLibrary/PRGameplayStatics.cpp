// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/PRGameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "AI/PRAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PRGameplayTags.h"
#include "Characters/PRCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/PRWorldUserWidget.h"
#include "Game/PRGameInstance.h"
#include "Interfaces/PRBPIDamageNumber.h"
#include <Player/PRPlayerController.h>
#include <Player/PRPlayerState.h>
#include "Components/PRSessionTrackerComponent.h"
#include "GameplayTagContainer.h"
#include <EnhancedInputSubsystems.h>
#include "AssetRegistry/AssetRegistryModule.h"

FDamageCalculationResult UPRGameplayStatics::CalculateFinalDamage(const UPRStatsComponent* AttackerStats, float BaseDamage, float BaseCritChance, float BaseCritMultiplier, const APRAIBase* Target)
{
	FDamageCalculationResult Result;
	if (!AttackerStats)
	{
		Result.FinalDamage = BaseDamage;
		return Result;
	}

	// --- 1. GET MODIFIERS FROM STATS COMPONENT ---
	const float AdditiveDamage = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Additive);
	const float MultiplicativeDamage = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Multiplicative);

	const float CritChanceBonus = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritChance);
	const float CritDamageBonus = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_CritDamage);

	// --- 2. CALCULATE INITIAL DAMAGE ---
	Result.FinalDamage = (BaseDamage + AdditiveDamage) * MultiplicativeDamage;

	// --- 3. CRIT CHANCE & CRIT DAMAGE LOGIC ---
	const float FinalCritChance = BaseCritChance + CritChanceBonus;
	if (FMath::FRand()*100 < FinalCritChance)
	{
		Result.bWasCriticalHit = true;
		const float FinalCritMultiplier = CritDamageBonus; // Was like this: const float FinalCritMultiplier = BaseCritMultiplier + CritDamageBonus;
		Result.FinalDamage *= FinalCritMultiplier;
	}

	// --- 4. DAMAGE TO ELITES & BOSSES LOGIC ---
	if (Target && (Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Elite) || Target->GetAITags().HasTag(NativeGameplayTags::EnemyTypes::TAG_Enemy_Type_Boss)))
	{
		const float EliteDamageBonus = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Elites);
		Result.FinalDamage *= EliteDamageBonus;
	}

	return Result;
}

float UPRGameplayStatics::ApplyRumbleDamage(UObject* WorldContextObject, AActor* DamagedActor, float BaseDamage, const FDamageCalculationResult& DamageResult, 
	FGameplayTag DamageSourceTag,AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass, 
	const FVector& KnockbackDirection, float KnockbackMagnitude, float StunChance, float StunDuration, USoundBase* HitSound)
{
	
	// --- 1. APPLY KNOCKBACK FIRST (OR INDEPENDENTLY) ---
	// Knockback should happen even if the damage is 0 or absorbed.
	if (KnockbackMagnitude > 0.f)
	{
		if (ACharacter* TargetCharacter = Cast<ACharacter>(DamagedActor))
		{
			FVector LaunchVelocity = KnockbackDirection * KnockbackMagnitude;
			TargetCharacter->LaunchCharacter(LaunchVelocity, true, true);
			
			// Close Input connection to notify the character it has been knocked back.
			if (APRCharacterBase* PRChar = Cast<APRCharacterBase>(TargetCharacter))
			{
				PRChar->OnKnockbackReceived();

			}
		}
	}
	// --- 2. APPLY STUN  ---
	if (StunDuration > 0.f && FMath::FRand() < StunChance)
	{
		UE_LOG(LogTemp, Warning, TEXT("STUN APPLIED! Chance was %.2f"), StunChance);
		// Get the Pawn from the damaged actor.
		if (APawn* DamagedPawn = Cast<APawn>(DamagedActor))
		{
			// Get the AI Controller of that Pawn.
			if (AAIController* AIController = Cast<AAIController>(DamagedPawn->GetController()))
			{
				// Get the Blackboard Component from the AI Controller.
				if (UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent())
				{
					// Set the "IsStunned" key to true.
					BlackboardComp->SetValueAsBool(NativeGameplayTags::State::TAG_State_IsStunned.GetModuleName(), true);

					// --- Set a timer to clear the stun ---
					// We need a UObject to set a timer on. A static class can't do it directly.
					// The simplest way is to use the DamagedActor's world.

					// Create a lambda function to be called by the timer.
					FTimerDelegate TimerDelegate;
					TimerDelegate.BindLambda([=]()
						{
							if (BlackboardComp)
							{
								BlackboardComp->SetValueAsBool(NativeGameplayTags::State::TAG_State_IsStunned.GetModuleName(), false);
							}
						});

					// Get the world from the damaged actor and set the timer.
					if (UWorld* World = DamagedActor->GetWorld())
					{
						FTimerHandle StunTimerHandle;
						World->GetTimerManager().SetTimer(StunTimerHandle, TimerDelegate, StunDuration, false);
					}
				}
			}
		}
	}

	// --- 3. APPLY THE STANDARD DAMAGE ---
	// This will trigger the target's TakeDamage function chain.
	const float ActualDamage = UGameplayStatics::ApplyDamage(DamagedActor, BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);

	// --- 4. LIFESTEAL LOGIC  ---
	if (ActualDamage > 0.f && DamageCauser)
	{
		// Is the one who dealt damage a player character?
		if (APRCharacterBase* Attacker = Cast<APRCharacterBase>(DamageCauser))
		{
			// Does the attacker have a stats component?
			if (UPRStatsComponent* AttackerStats = Attacker->GetStatsComponent())
			{
				const float LifestealPercent = AttackerStats->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_LifeSteal);
				if (LifestealPercent > 0.f)
				{
					// Calculate and apply the healing
					const float HealthToSteal = ActualDamage * LifestealPercent;
					const int32 RoundedHealth = FMath::RoundToInt(HealthToSteal);
					if (RoundedHealth > 0)
					{
						AttackerStats->Heal(RoundedHealth);
						UE_LOG(LogTemp, Log, TEXT("%s lifesteals %d health."), *Attacker->GetName(), RoundedHealth);
						if (AActor* OwnerActor = AttackerStats->GetOwner())
						{
							if (APRPlayerState* AttackerPS = Cast<APRPlayerState>(OwnerActor))
							{
								if (AttackerPS->TrackerComponent)
								{
									AttackerPS->TrackerComponent->AddStat(NativeGameplayTags::Tracker::TAG_Tracker_Survival_Health_Healing_Lifesteal, (float)RoundedHealth);
								}
							}
						}
					}
				}
			}
		}
	}
	// --- SPAWN DAMAGE NUMBER ---
	// We need to determine if it was a crit. This requires more data.
	// Let's pass the FDamageCalculationResult to this function.
	// For now, let's just spawn a non-crit number.
	if (ActualDamage > 0.f && WorldContextObject)
	{
		// Check if the damage dealer is a Player
		if (APRPlayerController* PC = Cast<APRPlayerController>(EventInstigator))
		{
			// Send the visual/audio cue ONLY to the player who dealt the damage.
			PC->Client_ShowDamageEffect(DamagedActor, ActualDamage, DamageResult.bWasCriticalHit, HitSound);
		}
	}

	// --- 5. TRACK DAMAGE DEALT STATISTIC ---
	if (ActualDamage > 0.f)
	{
		if (APRCharacterBase* PlayerChar = Cast<APRCharacterBase>(DamageCauser))
		{
			if (APRPlayerState* PS = PlayerChar->GetPlayerState<APRPlayerState>())
			{
				if (PS->TrackerComponent)
				{
					// Total Damage
					PS->TrackerComponent->AddStat(NativeGameplayTags::Tracker::TAG_Tracker_Main_Combat_DamageDealt, ActualDamage);

					// For damage breakdown
					if (DamageSourceTag.IsValid())
					{
						// Example: Add damage to "Item.Weapon.Axe" tag
						// Dont forget we need to set the DamageSourceTag when calling this function!
						PS->TrackerComponent->AddStat(DamageSourceTag, ActualDamage);
					}
				}
			}
		}
	}
	return ActualDamage;
}

TArray<AActor*> UPRGameplayStatics::SortActorsByDistance(const FVector& TargetLocation, const TArray<AActor*>& ActorsToSort)
{
	TArray<AActor*> SortedActors = ActorsToSort;

	// The Sort() function allows us to specify how to compare two elements
	// using a “lambda” (anonymous function).
	SortedActors.Sort([&](const AActor& A, const AActor& B) {
		const float DistA = FVector::DistSquared(A.GetActorLocation(), TargetLocation);
		const float DistB = FVector::DistSquared(B.GetActorLocation(), TargetLocation);
		return DistA < DistB;
		});

	return SortedActors;
}

void UPRGameplayStatics::SpawnDamageNumber(UObject* WorldContextObject, float Damage, bool bIsCrit, AActor* TargetActor)
{

	if (!WorldContextObject || !TargetActor) return;

	// 1. Get our custom GameInstance to find the widget class
	UPRGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance<UPRGameInstance>();
	if (!GameInstance || !GameInstance->DamageNumberWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageNumberWidgetClass is not set in BP_GameInstance!"));
		return;
	}

	// 2. Get the local PlayerController to create the widget for
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PC) return;

	// 3. Create the widget instance
	UPRWorldUserWidget* DamageWidget = CreateWidget<UPRWorldUserWidget>(PC, GameInstance->DamageNumberWidgetClass);
	if (DamageWidget)
	{
		// 4. Set the actor for the widget to follow
		DamageWidget->AttachedActor = TargetActor;

		// --- 5. INITIALIZE THE WIDGET WITH DATA (THE FIX) ---
		// Check if the newly created widget actually implements our interface
		if (DamageWidget->GetClass()->ImplementsInterface(UPRBPIDamageNumber::StaticClass()))
		{
			// If it does, we can safely call the interface function to pass the damage data.
			IPRBPIDamageNumber::Execute_InitializeNumber(DamageWidget, Damage, bIsCrit);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget '%s' does not implement BPI_DamageNumber interface! Cannot initialize."), *DamageWidget->GetName());
		}

		// 6. Add the initialized widget to the screen
		DamageWidget->AddToViewport();
	}
}

bool UPRGameplayStatics::IsKeyMappedToAction(UObject* WorldContextObject, FKey Key, const UInputAction* Action)
{
	if (!Action || !WorldContextObject) return false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!PC) return false;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		// Oyuncunun þu anki tuþ atamalarýný sorguluyoruz
		TArray<FKey> MappedKeys = Subsystem->QueryKeysMappedToAction(Action);

		// Basýlan tuþ (Key), bu listenin içinde var mý?
		return MappedKeys.Contains(Key);
	}

	return false;
}

bool UPRGameplayStatics::IsGameWindowFocused()
{
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->Viewport)
	{
		return GEngine->GameViewport->Viewport->IsForegroundWindow();
	}
	return false;
}

TArray<FAssetData> UPRGameplayStatics::FindAllAssetsOfClass(UClass* BaseClass)
{
#if WITH_EDITOR
	TArray<FAssetData> AssetDataList;
	if (!BaseClass) return AssetDataList;

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// Search according to the Class Path (Recursive classes true)
	FARFilter Filter;
	Filter.ClassPaths.Add(BaseClass->GetClassPathName());
	Filter.bRecursiveClasses = true;

	AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

	return AssetDataList;
#endif
}

void UPRGameplayStatics::AddMissingItemToLootTable(UDataTable* DataTable, UPRItemDefinition* ItemDef, float DefaultWeight)
{
#if WITH_EDITOR
	if (!DataTable || !ItemDef) return;

	// 1. Create Row Name
	// Generally, using the Asset name is the cleanest approach (e.g., DA_Magnet)
	FName RowName = ItemDef->GetFName();

	// 2. Is there already a control?
	if (DataTable->GetRowNames().Contains(RowName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Item %s already exists in table!"), *RowName.ToString());
		return;
	}

	// 3. Create and Populate the Structure
	// Note: This uses a hardcoded FLootTableRow.
	// If we have different tables, we need to write Generic Reflection, but this is sufficient for now.
	FLootTableRow NewRow;
	NewRow.ItemDefinition = ItemDef;
	NewRow.Weight = DefaultWeight;

	// 4. Add to Table
	DataTable->AddRow(RowName, NewRow);

	// 5. Tell the editor, “This file has been changed, mark it with a star.”
	DataTable->MarkPackageDirty();

	UE_LOG(LogTemp, Log, TEXT("Added %s to Loot Table."), *RowName.ToString());
#endif
}

void Generic_GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag TagToFind, void* OutRowPtr, FProperty* OutRowProp, ERowResult& OutResult)
{
	OutResult = ERowResult::NotFound;

	if (!DataTable || !OutRowPtr || !OutRowProp) return;

	// 1. Get the Struct type used by the Data Table
	const UScriptStruct* TableStruct = DataTable->GetRowStruct();

	// 2. Is the Struct connected to the output pin the same as the table's Struct? (Security)
	const FStructProperty* StructProp = CastField<FStructProperty>(OutRowProp);
	if (!StructProp || StructProp->Struct != TableStruct)
	{
		UE_LOG(LogTemp, Error, TEXT("GetDataTableRowByTag: Output Struct type does not match DataTable Struct type!"));
		return;
	}

	// 3. Search for a variable of type “GameplayTag” in the Struct (Automatic Detection)
	FStructProperty* TagProperty = nullptr;

	for (TFieldIterator<FProperty> It(TableStruct); It; ++It)
	{
		if (FStructProperty* StructPropInRow = CastField<FStructProperty>(*It))
		{
			if (StructPropInRow->Struct->GetFName() == FName("GameplayTag"))
			{
				TagProperty = StructPropInRow;
				break; // Use the first Tag variable you find (usually the first ID), the problem with that you need to set id tag first. If you use multiple tags, you need to be careful.
			}
		}
	}

	if (!TagProperty)
	{
		UE_LOG(LogTemp, Error, TEXT("GetDataTableRowByTag: No 'GameplayTag' property found in struct '%s'"), *TableStruct->GetName());
		return;
	}

	// 4. Scan the table
	for (auto It : DataTable->GetRowMap())
	{
		uint8* RowData = It.Value;

		//  Read the tag value
		FGameplayTag* ValuePtr = TagProperty->ContainerPtrToValuePtr<FGameplayTag>(RowData);

		// Compare
		if (ValuePtr && *ValuePtr == TagToFind)
		{
			// FOUND IT! 
			// Copy the row data (RowData) to the output pin (OutRowPtr).
			TableStruct->CopyScriptStruct(OutRowPtr, RowData);

			OutResult = ERowResult::Found;
			return;
		}
	}
}

// This function is called by the Unreal VM. It resolves the parameters and passes them to the function above.
DEFINE_FUNCTION(UPRGameplayStatics::execGetDataTableRowByTag)
{
	// 1. Read Parameters
	P_GET_OBJECT(UDataTable, DataTable);
	P_GET_STRUCT(FGameplayTag, TagToFind);

	// 2. Resolve the Wildcard (OutRow) parameter
	Stack.StepCompiledIn<FProperty>(NULL);
	void* OutRowPtr = Stack.MostRecentPropertyAddress;
	FProperty* OutRowProp = Stack.MostRecentProperty;

	// 3. Read the Enum (Execs) parameter
	P_GET_ENUM_REF(ERowResult, OutResult);

	P_FINISH;

	// 4. Do the real work
	Generic_GetDataTableRowByTag(DataTable, TagToFind, OutRowPtr, OutRowProp, OutResult);
}


