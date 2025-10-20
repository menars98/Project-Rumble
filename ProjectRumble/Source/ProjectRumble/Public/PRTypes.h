#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "GameplayTagContainer.h"
#include "PRTypes.generated.h" 

class UPRUpgradeData;

UENUM(BlueprintType)
enum class EFaction : uint8
{
    Player,
    Enemy,
    Neutral
};

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
    NewWeapon,
    UpgradeWeapon,
    NewPassiveItem, // Tomes, Relics etc.
    UpgradePassiveItem,
    StatBonus // A simple, direct stat increase probably we wont use but its for test only right now
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Weapon,
    Tome,
    Relic,
    // Can add more types in the future
};

UENUM(BlueprintType)
enum class EStatDisplayType : uint8
{
    // Display as a flat number (e.g., 100, 10, 0)
    Flat,

    // Display as a percentage (e.g., 1%, 0%)
    Percentage,

    // Display as a multiplier (e.g., 1.0x, 1.2x)
    Multiplier
};

USTRUCT(BlueprintType)
struct FStatDefinition : public FTableRowBase 
{
    GENERATED_BODY()

public:

    // The stat's unique identifier (ID). We will access the stat using this ID in the code.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FGameplayTag StatID; 

    // The name to be displayed to the player in the stat. FText supports the game's localization.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    float DefaultValue;

    // Should this stat be displayed on the character's main stats panel? 
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    bool bShouldDisplayOnPanel = true; 

    /** How should this stat's value be formatted in the UI? */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    EStatDisplayType DisplayType = EStatDisplayType::Flat;
};

//This Struct now useless @TODO Delete everything that uses it or refactor it. (We use FPotentialUpgradeEffect right now, so check PRItemDefinition.)
// Represents a single effect that an upgrade can apply to a stat.
USTRUCT(BlueprintType)
struct FUpgradeEffect
{
    GENERATED_BODY()

    // Which stat does this effect modify?
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TargetStat;
    // The magnitude of the effect will be a random value between Min and Max.
    // For a fixed value, set Min and Max to be the same.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
    float MinMagnitude;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
    float MaxMagnitude;
};

USTRUCT(BlueprintType)
struct FPotentialUpgradeEffect
{
    GENERATED_BODY()

    /** Which stat can be upgraded? (e.g., Stat.Offense.Damage) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TargetStat;
    /** The minimum possible value for this effect at its base level (e.g., Common rarity, Level 1). */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
    float BaseMinMagnitude;

    /** The maximum possible value for this effect at its base level. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
    float BaseMaxMagnitude;

    /**
     * How much extra bonus is added for each rarity level above Common?
     * This value will be multiplied by the rarity tier (e.g., Rare is tier 2, so 2 * Bonus).
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
    float BonusPerRarityTier;

    /**
     * How likely is this specific stat to be chosen from the pool of potential effects?
     * A higher weight means a higher chance.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weight")
    float SelectionWeight = 1.0f;
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDamage = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseCooldown = 2.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseCritChance = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseCritDamageMultiplier = 2.0f; // Default crit is 200% damage

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseProjectileSpeed = 1500.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseSize = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseKnockback = 500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseDuration = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 BaseProjectileCount = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 BaseProjectileBounce = 1;
};

USTRUCT(BlueprintType)
struct FDamageCalculationResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float FinalDamage = 0.f;

    UPROPERTY(BlueprintReadOnly)
    bool bWasCriticalHit = false;
};