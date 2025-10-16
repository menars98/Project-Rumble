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
enum class EModifierOperation : uint8
{
    Additive,      // Adds to the base value (e.g., +10 HP, +1 Projectile)
    Multiplicative // Multiplies the value (e.g., +10% Damage, which is * 1.1)
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

USTRUCT(BlueprintType)
struct FStatDefinition : public FTableRowBase 
{
    GENERATED_BODY()

public:

    // Stat'ýn benzersiz kimliði (ID). Kod içinde bu ID ile stat'a eriþeceðiz.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FGameplayTag StatID; 

    // The name to be displayed to the player in the stat. FText supports the game's localization.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    float DefaultValue;


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

    // How is the value applied?
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EModifierOperation Operation;

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

    /** How is the value applied? Additive or Multiplicative? */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EModifierOperation Operation;

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