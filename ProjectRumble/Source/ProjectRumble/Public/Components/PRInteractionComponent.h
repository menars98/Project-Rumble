// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PRInteractionComponent.generated.h"

class UBPI_Interactable;
class UPRWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRUMBLE_API UPRInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPRInteractionComponent();

	// -- PUBLIC FUNCTION FOR PLAYER INPUT --
	void PrimaryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);

	// Finds the best interactable actor in front of the player.
	void FindBestInteractable();

	// The currently focused interactable actor.
	UPROPERTY()
	AActor* FocusedActor;

	// -- TRACE PROPERTIES --
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	// -- UI --
	// The widget class to display when an interactable is in focus (e.g., "Press E").
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UPRWorldUserWidget> DefaultWidgetClass;

	// The instance of the interaction widget.
	UPROPERTY()
	TObjectPtr<UPRWorldUserWidget> DefaultWidgetInstance;

};
