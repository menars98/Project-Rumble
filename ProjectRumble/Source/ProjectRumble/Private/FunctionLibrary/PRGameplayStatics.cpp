// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/PRGameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include "AI/PRAIBase.h"
#include "AI/PRAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PRGameplayTags.h"
#include "Characters/PRCharacterBase.h"
#include "Kismet/GameplayStatics.h"

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
		const float EliteDamageBonus = 1.0f + AttackerStats->GetStatValue(NativeGameplayTags::Stats::Offense::TAG_Stat_Offense_Damage_Elites);
		Result.FinalDamage *= EliteDamageBonus;
	}

	return Result;
}

float UPRGameplayStatics::ApplyRumbleDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass, const FVector& KnockbackDirection, float KnockbackMagnitude, float StunChance, float StunDuration)
{
	

	// --- 1. APPLY KNOCKBACK FIRST (OR INDEPENDENTLY) ---
	// Knockback should happen even if the damage is 0 or absorbed.
	if (KnockbackMagnitude > 0.f)
	{
		if (ACharacter* TargetCharacter = Cast<ACharacter>(DamagedActor))
		{
			FVector LaunchVelocity = KnockbackDirection * KnockbackMagnitude;
			TargetCharacter->LaunchCharacter(LaunchVelocity, true, true);
			
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
