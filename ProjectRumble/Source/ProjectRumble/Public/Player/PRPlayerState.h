// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTagContainer.h"
#include "PRPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatsComponentReady, UPRStatsComponent*, StatsComponent);


class UPRStatsComponent;
class UPRInventoryComponent;
class UPRSessionTrackerComponent;

UCLASS()
class PROJECTRUMBLE_API APRPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APRPlayerState();

	// Component to manage the player's stats (Health, XP, Modifiers, etc.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", ReplicatedUsing = OnRep_StatsComponent)
	TObjectPtr<UPRStatsComponent> StatsComponent;

	// Component to manage the player's inventory (Weapons, Tomes, Relics, etc.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", ReplicatedUsing = OnRep_InventoryComponent)
	TObjectPtr<UPRInventoryComponent> InventoryComponent;

	// Broadcasts when the StatsComponent is valid and ready to be bound to.
	UPROPERTY(BlueprintAssignable)
	FOnStatsComponentReady OnStatsComponentReady;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPRSessionTrackerComponent> TrackerComponent;

	UFUNCTION(BlueprintCallable, Category = "Lobby")
	void SetIsReady(bool bReady);

	// Server-side setter
	void SetKillerInfo(FText Name, FGameplayTag Tag);

	UFUNCTION(BlueprintPure, Category = "Lobby")
	bool GetIsReady() const { return bIsReady; }

	// Replicated properties to store killer info
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Game|Stats")
	FText KillerName;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Game|Stats")
	FGameplayTag KillerTag;
protected:

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// -- REPLICATION NOTIFY FUNCTIONS --
	UFUNCTION()
	void OnRep_StatsComponent();

	UFUNCTION()
	void OnRep_InventoryComponent();

	UFUNCTION(Server, Reliable)
	void Server_SetIsReady(bool bReady);

	// -- LOBBY FUNCTIONALITY --
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Lobby")
	bool bIsReady = false;
private:
	void InitializeStatsComponent();
	void InitializeInventoryComponent();
};
