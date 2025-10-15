// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PRPlayerController.generated.h"

class UDataTable;
class UUserWidget;
class UPRUpgradeData;

UCLASS()
class PROJECTRUMBLE_API APRPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;


protected:
	// -- REWARD SYSTEM --
	// The Data Table containing all possible stat upgrades (for the prototype).
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rewards")
	TObjectPtr<UDataTable> RewardDataTable;

	// Array to hold the rewards that are currently being offered to the player.
	// We make it BlueprintReadOnly so the UI can read it.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rewards")
	TArray<TObjectPtr<UPRUpgradeData>> OfferedRewards;

	// -- UI --
	// The Level Up screen widget class. Assigned in the BP_PlayerController Blueprint.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LevelUpWidgetClass;

	// The instance of the level up screen, so we can remove it later.
	UPROPERTY()
	TObjectPtr<UUserWidget> LevelUpWidgetInstance;

	// -- CORE --
	// Called when this controller possesses a pawn (character).
	// This is a more reliable place than BeginPlay to bind to player-specific delegates.
	virtual void OnPossess(APawn* InPawn) override;

	// Called by the StatsComponent's OnLevelUpDelegate.
	UFUNCTION()
	void ShowLevelUpScreen(int32 NewLevel);

public:
	// Called by the UI Widget when a player clicks on a reward button.
	UFUNCTION(BlueprintCallable, Category = "Rewards")
	void ApplyReward(UPRUpgradeData* ChosenUpgrade);
};
