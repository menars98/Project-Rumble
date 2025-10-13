#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "PRTypes.generated.h" 

UENUM(BlueprintType)
enum class EFaction : uint8
{
    Player,
    Enemy,
    Neutral
};

USTRUCT(BlueprintType)
struct FStatDefinition : public FTableRowBase 
{
    GENERATED_BODY()

public:

    // Stat'ýn benzersiz kimliði (ID). Kod içinde bu ID ile stat'a eriþeceðiz.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FName StatID;

    // The name to be displayed to the player in the stat. FText supports the game's localization.
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat Definition")
    float DefaultValue;


};

