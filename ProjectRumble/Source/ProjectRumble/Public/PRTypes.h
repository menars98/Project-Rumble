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
    Item,
    Relic
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

USTRUCT(BlueprintType)
struct FPotentialUpgradeEffect
{
    GENERATED_BODY()

    /** Which stat can be upgraded? (e.g., Stat.Offense.Damage) */
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FGameplayTag TargetStat;
    /** How should this stat's value be formatted in the UI? */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    EStatDisplayType DisplayType = EStatDisplayType::Flat;
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseStunChance = 0.0f; // 0.0 to 1.0

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float BaseStunDuration = 0.5f;
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

USTRUCT(BlueprintType)
struct FLootTableRow : public FTableRowBase
{
    GENERATED_BODY()

public:
    // The item that can drop from this chest.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
    TObjectPtr<class UPRItemDefinition> ItemDefinition;

    // How likely is this item to drop relative to others? Higher = more likely.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
    float Weight = 1.0f;

    // (Optional) Minimum/Maximum quantity if we want stacks of items later.
};

// Defines a single type of loot that can be dropped (e.g., 15 XP).
USTRUCT(BlueprintType)
struct FLootDrop
{
    GENERATED_BODY()

    // The class of the pickup to spawn (e.g., BP_XPShard, BP_GoldCoin).
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AActor> PickupClass;

    // The base value of this drop (e.g., 15 for XP, 5 for Gold).
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Value = 0.f;

    // Chance for this specific drop to happen (0.0 to 1.0).
    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float DropChance = 1.0f; // 100% chance by default
};

// Defines a collection of possible drops (e.g., a Goblin's loot profile).
USTRUCT(BlueprintType)
struct FLootProfile : public FTableRowBase
{
    GENERATED_BODY()

public:
    // The tag that identifies this loot profile (e.g., "Enemy.Type.Goblin").
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
    FGameplayTag ProfileTag;

    // A list of all possible items that can be dropped from this profile.
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FLootDrop> PossibleDrops;
};

USTRUCT(BlueprintType)
struct PROJECTRUMBLE_API FPRWeaponAttackStats
{
    GENERATED_BODY()

    // Constructor with defaults to ensure valid values
    FPRWeaponAttackStats()
        : Damage(0.0f), CritChance(0.0f), CritMultiplier(1.0f), SizeMultiplier(1.0f), KnockbackMagnitude(0.0f),
        StunChance(0.0f), StunDuration(0.0f), LifeDuration(0.0f), ProjectileCount(1),
        ProjectileSpeed(0.0f), ProjectileBounce(0), TickRate(0.0f) {
    }

    // 1. Core Combat Properties (Used by most/all attacks)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float CritChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float CritMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float KnockbackMagnitude;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float StunChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float StunDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Combat")
    float AttackSpeed;
    // 2. Projectile/Area Properties (Used only by relevant attack types)

    // Multiplier for the projectile/area size.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Movement")
    float SizeMultiplier;

    // How long the attack actor (projectile/aura) will last.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|LifeCycle")
    float LifeDuration;

    // Projectile count (Used by weapons like Arrow, Axe multi-throw).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Projectile")
    float ProjectileCount;

    // The speed at which the projectile travels.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Projectile")
    float ProjectileSpeed;

    // How many times a projectile can bounce off a wall/enemy.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|Projectile")
    float ProjectileBounce;

    // For DOT/Aura attacks, the frequency of damage application (in seconds).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rumble|AuraDOT")
    float TickRate;
};

// --- FOR AI ---
USTRUCT(BlueprintType)
struct PROJECTRUMBLE_API FAIStats : public FTableRowBase
{
    GENERATED_BODY()

public:
    // --- UI  ---
	// The unique identifier (ID) for this enemy type.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
    FGameplayTag EnemyID;

	// The name to be displayed to the player in the UI.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
    FText DisplayName;
	// A brief description of the enemy, shown in tooltips or info panels.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
    FText Description;
	// An icon representing the enemy in the UI.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Metadata")
    TObjectPtr<UTexture2D> Icon;

    /**
     * Array of all base stats for this AI. Each element holds a FGameplayTag and its starting value.
     * e.g., Element 0: [Tag: Stat.Defense.MaxHP, Value: 30.0]
     */
        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Stats")
    TArray<FStatDefinition> BaseStats;

};