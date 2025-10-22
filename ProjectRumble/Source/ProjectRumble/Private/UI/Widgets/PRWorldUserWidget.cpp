// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRWorldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPRWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If we don't have an actor to follow, or we are not in a valid world, hide the widget.
	if (!IsValid(AttachedActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("WorldWidget: AttachedActor is NOT valid. Hiding."));
		RemoveFromParent();
		return;
	}

	FVector2D ScreenPosition;

	// Get the 3D world location to track.
	FVector WorldLocation = AttachedActor->GetActorLocation() + WorldOffset;

	// Project the 3D world location to a 2D screen position.
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldLocation, ScreenPosition);

	UE_LOG(LogTemp, Log, TEXT("WorldWidget: Tracking %s. OnScreen: %s. ScreenPos: %s"),
		*AttachedActor->GetName(),
		bIsOnScreen ? TEXT("True") : TEXT("False"),
		*ScreenPosition.ToString());

	if (bIsOnScreen)
	{
		// If the location is on screen, set the widget's position.
		float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= ViewportScale; // Adjust for DPI scaling

		// Ensure the widget is visible
		if (GetVisibility() != ESlateVisibility::SelfHitTestInvisible)
		{
			SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		SetPositionInViewport(ScreenPosition);
	}
	else
	{
		// If the location is off screen, hide the widget.
		if (GetVisibility() != ESlateVisibility::Collapsed)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
