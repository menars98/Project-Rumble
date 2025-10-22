// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PRWorldUserWidget.generated.h"

class USceneComponent;

/**
 * A User Widget that can be attached to a specific actor in the world
 * and automatically position itself on the screen.
 */

UCLASS()
class PROJECTRUMBLE_API UPRWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// The actor that this widget is attached to and will follow on screen.
	// We make this "Expose on Spawn" so it can be set when the widget is created.
	// Also "BlueprintReadWrite" so we can set it from other Blueprints.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<AActor> AttachedActor;

protected:
	// Called every frame. We need Tick to update the widget's position.
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// The world space offset from the AttachedActor's location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FVector WorldOffset;

	// An optional component to attach to on the actor, instead of the actor's root.
	// For example, an "OverheadWidget" socket on a character's head bone.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<const USceneComponent> AttachedComponent;

};
