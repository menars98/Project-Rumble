// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PRTypes.h" 
#include "GameFramework/Actor.h"
#include "PRSpawnerManager.generated.h"


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

	// --- FUNCTIONS ---

	// The main spawn loop, called by the SpawnTimerHandle.
	void SpawnLoop();

	// Processes the wave timeline based on the current game time.
	void ProcessWaveTimeline();

};
