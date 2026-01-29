// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PRMapGenDefinition.generated.h"

USTRUCT(BlueprintType)
struct FPropSpawnRule
{
    GENERATED_BODY()

	// Which mesh to spawn
    UPROPERTY(EditAnywhere)
    TArray<UStaticMesh*> PossibleMeshes;

	// How dense the props are spawned (0-1)
    UPROPERTY(EditAnywhere)
    float Density = 0.5f;

    // Scale
    UPROPERTY(EditAnywhere)
    FVector2D ScaleRange = FVector2D(0.8f, 1.2f);
};

USTRUCT(BlueprintType)
struct FInteractableSpawnRule
{
    GENERATED_BODY()

    // Which Actor? (Örn: BP_Chest)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AActor> ActorClass;

    // How Much?
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 SpawnCount = 10;

	// Collision Radius to avoid overlapping
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CollisionRadius = 100.0f;

	// Minimum Distance Between same interactables (250 = 2.5 meters)
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MinDistanceBetween = 250.0f;
};


UCLASS()
class PROJECTRUMBLE_API UPRMapGenDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// Floor mesh
    UPROPERTY(EditDefaultsOnly, Category = "Floor")
    UStaticMesh* FloorMesh;

    UPROPERTY(EditDefaultsOnly, Category = "Size")
    int32 MapWidth = 50;

    UPROPERTY(EditDefaultsOnly, Category = "Size")
    int32 MapHeight = 50;

    // Only for visual  (Client-Side)
    UPROPERTY(EditDefaultsOnly, Category = "Props")
    TArray<FPropSpawnRule> DecorationProps;

    // Interactable objects (Replicated - Server Side)
    UPROPERTY(EditDefaultsOnly, Category = "Interactables")
    TArray<FInteractableSpawnRule> Interactables;
};
