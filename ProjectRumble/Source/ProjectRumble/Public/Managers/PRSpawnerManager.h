// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRTypes.h" 
#include "GameFramework/Actor.h"
#include "PRSpawnerManager.generated.h"

class UPRSpawnConfig;

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

	UPROPERTY(EditDefaultsOnly, Category = "Spawning|Config")
	TObjectPtr<UPRSpawnConfig> SpawnConfig;

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
	void ProcessWaveTimeline(float GameTime, float DifficultyMultiplier);
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
