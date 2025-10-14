// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PRPlayerState.h"
#include "Components/PRStatsComponent.h"

APRPlayerState::APRPlayerState()
{
    StatsComponent = CreateDefaultSubobject<UPRStatsComponent>(TEXT("StatsComponent"));
}