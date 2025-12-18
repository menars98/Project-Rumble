// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRTypes.h" 
#include "GameFramework/Actor.h"
#include "PRSpawnerManager.generated.h"

class UPRSpawnConfig;
class APRAIBase;

UCLASS()
class PROJECTRUMBLE_API APRSpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APRSpawnerManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

    // --- CONFIG ---
    UPROPERTY()
    TObjectPtr<UPRSpawnConfig> SpawnConfig;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    float SpawnRadius = 3000.f;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    float SpawnCheckInterval = 0.5f;

    UPROPERTY(EditDefaultsOnly, Category = "Spawning|Limits")
    int32 AbsoluteMaxAI = 600;

    // Index of the next boss event to trigger.
    int32 NextBossEventIndex = 0;

    // --- RUNTIME STATE ---

    // The "Deck" of enemies selected for THIS specific game run.
    // Key: Tier Tag (e.g., Tier 1), Value: List of Classes (e.g., Goblin, Skeleton)
    TMap<FGameplayTag, TArray<TSubclassOf<APRAIBase>>> CurrentRunDeck;

    // A cache of ALL possible enemies mapped by their Specific Type Tag.
    // Used for O(1) lookup when the timeline demands a specific enemy.
    // Key: Enemy Type Tag (e.g., "Enemy.Type.Goblin"), Value: The Class.
    TMap<FGameplayTag, TSubclassOf<APRAIBase>> SpecificEnemyCache;

    // Current limits
    int32 TargetAICount = 0;
    int32 CurrentMaxActiveAI = 0;

    FTimerHandle SpawnTimerHandle;

    // --- FUNCTIONS ---

    /**
     * Builds the "CurrentRunDeck" by filtering the catalog based on Biome
     * and picking random enemies based on RunDeckSelectionCounts.
     */
    void BuildRunDeck();

    void SpawnLoop();

    // Helper to process boss spawning
    void CheckBossEvents(float GameTime, ACharacter* Player);

    FVector FindSafeSpawnLocation(const FVector& CenterLocation, float Radius) const;

    /**
     * Decides which enemy class to spawn based on the current Game Time.
     * 1. Finds the active Segment.
     * 2. Rolls a Tier based on weights.
     * 3. Picks a random class from that Tier in the Run Deck.
     */
    TSubclassOf<APRAIBase> GetEnemyToSpawn(float GameTime);

    /**
   * Resolves a GameplayTag into an actual Enemy Class.
   * Checks if the tag is a Tier (picks from Deck) or a Specific Type (picks from Cache).
   */
    TSubclassOf<APRAIBase> ResolveSpawnTag(FGameplayTag Tag);
};
