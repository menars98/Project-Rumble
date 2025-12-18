// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRTypes.h"
#include "PRSpawnConfig.generated.h"

class APRAIBase;
class UCurveFloat;

// --- 1. THE CATALOG ENTRY (Database) ---
// Defines a single enemy type available in the game.
USTRUCT(BlueprintType)
struct FEnemyCatalogEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<APRAIBase> AIClass;

    // Is it Tier 1 (Weak), Tier 2, or Boss?
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TierTag;

    // Where does this enemy live? (e.g., Forest, Desert, or Global)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTagContainer BiomeTags;
};

// --- 2. THE TIMELINE SEGMENT (When do they spawn?) ---
// Instead of "Wave 1", we define rules for time periods.
USTRUCT(BlueprintType)
struct FSpawnSegment
{
    GENERATED_BODY()

    // When does this rule start? (Seconds)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float StartTime = 0.0f;

    /**
    * Mapping of GameplayTag to Weight.
    * The Tag can be EITHER a Tier Tag (e.g., "Enemy.Tier.1")
    * OR a Specific Enemy Type Tag (e.g., "Enemy.Type.Goblin").
    *
    * Example Horde Wave:
    * - "Enemy.Type.Goblin" : 100.0 (Only Goblins will spawn)
    *
    * Example Mixed Wave:
    * - "Enemy.Tier.1" : 50.0 (Random Tier 1s)
    * - "Enemy.Type.Cactus" : 50.0 (Specific Cactus)
    */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TMap<FGameplayTag, float> SpawnWeights;
};

USTRUCT(BlueprintType)
struct FBossSpawnEvent
{
    GENERATED_BODY()

    // At what second of the game should it appear? (e.g., 240.0 = 4th minute)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TriggerTime = 0.0f;

    // Which Boss?
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<APRAIBase> BossClass;

    // Should text appear on the screen when the boss appears? (Optional)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText WarningMessage;

    // Should normal spawning stop when the boss appears? (False if we want Horde logic, True if we want Duel)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bPauseNormalSpawns = false;
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
 * The Master Configuration Asset.
 * Contains both the "Database" of all enemies and the "Rules" for the current level.
 */
UCLASS()
class PROJECTRUMBLE_API UPRSpawnConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
    // List of specific Boss Events (Independent of the continuous spawn waves)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pacing")
    TArray<FBossSpawnEvent> BossEvents;

    // --- DATABASE ---
    // List of ALL enemies in the entire game.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Database")
    TArray<FEnemyCatalogEntry> EnemyCatalog;

    // --- LEVEL SETTINGS ---
    // Which biome is this config for? (Used to filter the catalog)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Settings")
    FGameplayTag LevelBiomeTag;

    // How many distinct enemy types from each Tier should be selected for this run?
    // e.g., "Pick 3 random enemies from Tier 1", "Pick 2 from Tier 2".
    // This creates the "Roguelike Deck".
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Settings")
    TMap<FGameplayTag, int32> RunDeckSelectionCounts;

    // --- PACING ---
    // Controls the TOTAL NUMBER of enemies alive over time.
    // X: Time (Seconds), Y: Max Active AI Count.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pacing")
    TObjectPtr<UCurveFloat> SpawnCapCurve;

    // Defines the rules (weights) for different time periods.
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pacing")
    TArray<FSpawnSegment> Timeline;

};
