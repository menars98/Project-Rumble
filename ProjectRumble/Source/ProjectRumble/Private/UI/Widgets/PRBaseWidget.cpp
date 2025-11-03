// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PRBaseWidget.h"
#include "Kismet/GameplayStatics.h"

void UPRBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (InitializeSound)
	{

		UGameplayStatics::PlaySound2D(this, InitializeSound);
	}
}
