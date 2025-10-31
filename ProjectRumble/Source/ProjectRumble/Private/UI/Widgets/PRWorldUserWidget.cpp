// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRWorldUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/Character.h" 
#include "Components/SizeBox.h"

void UPRWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If we don't have an actor to follow, or we are not in a valid world, hide the widget.
	if (!IsValid(AttachedActor))
	{
		// UE_LOG(LogTemp, Warning, TEXT("WorldWidget: AttachedActor is NOT valid. Hiding.")); // Better to avoid spamming logs on removal
		RemoveFromParent();
		return;
	}

	FVector WorldPositionToFollow;

	// 1. Try to use an Attached Component if set.
	if (IsValid(AttachedComponent))
	{
		// Use the component's location as the base.
		WorldPositionToFollow = AttachedComponent->GetComponentLocation();
	}
	// 2. Otherwise, try to find a socket on the AttachedActor's root component.
	else if (!AttachSocketName.IsNone())
	{
		// Get the root component of the actor.
		USceneComponent* Root = AttachedActor->GetRootComponent();
		if (Root && Root->DoesSocketExist(AttachSocketName))
		{
			WorldPositionToFollow = Root->GetSocketLocation(AttachSocketName);
		}
		else
		{
			// Fallback to Actor Location if the socket is not found.
			WorldPositionToFollow = AttachedActor->GetActorLocation();
		}
	}
	// 3. Fallback to Actor Location.
	else
	{
		WorldPositionToFollow = AttachedActor->GetActorLocation();
	}
	UE_LOG(LogTemp, Log, TEXT("WorldWidget: SocketName %s"), *AttachSocketName.ToString());

	// Apply the user-defined offset.

	FVector2D ScreenPosition;
	// Project the calculated world position to the screen.
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldPositionToFollow, ScreenPosition);


	// UE_LOG for tracking purposes (can be removed later).
	 UE_LOG(LogTemp, Log, TEXT("WorldWidget: Tracking %s. OnScreen: %s. ScreenPos: %s"),
	 	*AttachedActor->GetName(),
	 	bIsOnScreen ? TEXT("True") : TEXT("False"),
	 	*ScreenPosition.ToString());

	// ... (The rest of your logic for scaling and setting render translation remains the same)
	if (bIsOnScreen)
	{

		float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		if (ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}

	if (ParentSizeBox)
	{
		// Hide the widget if it's not on screen.
		ParentSizeBox->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}
