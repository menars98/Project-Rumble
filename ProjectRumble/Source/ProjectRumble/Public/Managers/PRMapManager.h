// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PRMapManager.generated.h"

class UPRMapGenDefinition;
class UBoxComponent;


UCLASS()
class PROJECTRUMBLE_API APRMapManager : public AActor
{
	GENERATED_BODY()
	
public:

    APRMapManager();

protected:

    virtual void BeginPlay() override;

    // Config
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rumble | Config")
    TObjectPtr<UPRMapGenDefinition> MapDefinition;

    // Replicated Seed
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rumble | Config", Replicated)
    int32 MapSeed = 12345;

    // Visualize the Spawn Area (Debug)
    UPROPERTY(VisibleAnywhere, Category = "Rumble | Components")
    TObjectPtr<UBoxComponent> SpawnAreaBox;

    /// Functions

    UFUNCTION()
    void OnRep_MapSeed();

    void GenerateMap();

	// Create Static Environment (Only Client)
    void SpawnStaticEnvironment(FRandomStream& Stream);

	// Create Interactable Objects (Only Server)
    void SpawnInteractables();

    /**
    * Finds a random X,Y point and traces down to find the ground.
    * @return Found ground position (or ZeroVector).
    */
    FVector GetRandomGroundLocation(const FRandomStream& Stream) const;

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


};
