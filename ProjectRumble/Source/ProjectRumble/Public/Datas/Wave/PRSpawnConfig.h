// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRTypes.h"
#include "PRSpawnConfig.generated.h"

class APRAIBase;
// --- Waves ---
USTRUCT(BlueprintType)
struct FBossWaveData
{
    GENERATED_BODY()

    /** The Boss/Elite AI class to spawn (must be APRAIBase derivative). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<APRAIBase> BossAIClass;

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
    TSubclassOf<APRAIBase> AIClass;

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

USTRUCT(BlueprintType)
struct FEndlessWaveData
{
    GENERATED_BODY()

    /**
     * When does this phase start? (Relative to Endless Mode Start)
     * 0.0 = Starts immediately at 10 mins.
     * 60.0 = Starts at 11 mins.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float StartTimeOffset = 0.0f;

    /** The enemy type to spawn in this phase. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<class APRAIBase> AIClass;

    /**
     * The color tint to apply to the enemy to signify strength.
     * The enemy material must have a vector parameter named "Tint" or "BodyColor".
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FLinearColor ColorTint = FLinearColor::White;
};

struct FSpawnWeight
{
    TSubclassOf<APRAIBase> AIClass;
    float Weight;
};
// --- END ----

/**
 * A Data Asset to hold the entire spawn configuration for a level.
 * This allows designers to create different spawn profiles (Easy, Hard, ForestMap, etc.)
 */
UCLASS()
class PROJECTRUMBLE_API UPRSpawnConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	// The sequence of normal enemy waves.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<FWaveData> Waves;

	// The sequence of boss encounters.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TArray<FBossWaveData> Bosses;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning|Endless")
    TArray<FEndlessWaveData> EndlessTimeline;

	// Base settings can also go here
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Limits")
	int32 BaseMaxActiveAI = 200;

};
