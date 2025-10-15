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

// An entry in an upgrade pool, used for random selection of upgrades.
USTRUCT(BlueprintType)
struct FUpgradePoolEntry : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UPRUpgradeData> UpgradeDataAsset;

    // How likely is this upgrade to be picked? (Higher is more likely)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Weight = 1.0f;
};