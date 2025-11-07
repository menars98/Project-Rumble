// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRTypes.h" 
#include "GameFramework/Actor.h"
#include "PRSpawnerManager.generated.h"


USTRUCT(BlueprintType)
struct FBossWaveData
{
	GENERATED_BODY()

	/** The Boss/Elite AI class to spawn (must be APRAIBase derivative). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class APRAIBase> BossAIClass;

	/** Game time (in seconds) when this boss should spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeToSpawn;
};

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	// What type of AI to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class APRAIBase> AIClass;

	// How many of this AI should be added to the target population?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PopulationIncrease;

	// When does this wave start, in seconds from the beginning of the match?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeToStart;

	/**
	* The initial percentage of this AI type in the active pool (at TimeToStart).
	* e.g., 0.5f means this AI will make up 50% of all spawned units when its wave starts.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave|Distribution")
	float InitialSpawnPercentage; 

	/**
	* The rate at which this AI's spawn percentage DECAYS over time (per minute).
	* e.g., 0.05f means it loses 5% of its contribution per minute.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave|Distribution")
	float PercentageDecayPerMinute; 

	/** The minimum percentage this AI can contribute to the spawn pool, even after decay. (e.g., 0.05f for 5% minimum chance). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave|Distribution")
	float MinimumSpawnPercentage;
};

struct FSpawnWeight
{
	TSubclassOf<APRAIBase> AIClass;
	float Weight;
};

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

	// --- CONFIGURATION ---

	// A timeline of all waves scheduled for the match. Must be sorted by TimeToStart.
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Waves")
	TArray<FWaveData> WaveTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Bosses")
	TArray<FBossWaveData> BossTimeline;

	/** The radius around the player where enemies can be spawned. */
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Location")
	float SpawnRadius = 3000.f;

	// The base maximum number of AI that can be active at once.
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Limits")
	int32 BaseMaxActiveAI = 200;

	// In Endless Mode, how much is MaxActiveAI increased per minute?
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Limits")
	int32 MaxAIIncreasePerMinute_Endless = 50;

	// How often (in seconds) should the spawner try to spawn new units?
	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Timing")
	float SpawnCheckInterval = 0.5f;

	// --- RUNTIME STATE ---

	// The current target number of AI in the world.
	int32 TargetAICount;

	// The current maximum number of AI allowed. Can increase in endless mode.
	int32 CurrentMaxActiveAI;

	// Timer for checking when to spawn.
	FTimerHandle SpawnTimerHandle;

	// Index of the next wave in the timeline to process.
	int32 NextWaveIndex;

	// Index of the next boss wave to process.
	int32 NextBossIndex;

	// --- FUNCTIONS ---

	// The main spawn loop, called by the SpawnTimerHandle.
	void SpawnLoop();

	// Processes the wave timeline based on the current game time.
	void ProcessWaveTimeline(float GameTime);
	// Processes the boss timeline based on the current game time.
	void ProcessBossTimeline(float GameTime);
private:
	// Gets a random AI class from all currently active waves.
	TSubclassOf<class APRAIBase> GetWeightedRandomActiveAIClass(float GameTime) const;

	/**
	 * Finds a valid spawn location by line-tracing down to the ground from a point around the player.
	 * @param CenterLocation The player's location.
	 * @param Radius The radius around the player to check for a spawn location.
	 * @return A point on the ground (Z-coordinate snapped to the terrain) or FVector::ZeroVector if failed.
	 */
	FVector FindSafeSpawnLocation(const FVector& CenterLocation, float Radius) const;
};
