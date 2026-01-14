// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/PRItemDefinition.h"
#include <Net/UnrealNetwork.h>

void UPRItemDefinition::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPRItemDefinition, DisplayName);
	DOREPLIFETIME(UPRItemDefinition, Icon);
	DOREPLIFETIME(UPRItemDefinition, ItemType);
	DOREPLIFETIME(UPRItemDefinition, NumEffects_Common);
	DOREPLIFETIME(UPRItemDefinition, NumEffects_Uncommon);
	DOREPLIFETIME(UPRItemDefinition, NumEffects_Rare);
	DOREPLIFETIME(UPRItemDefinition, NumEffects_Epic);
	DOREPLIFETIME(UPRItemDefinition, NumEffects_Legendary);
	DOREPLIFETIME(UPRItemDefinition, PotentialUpgradeEffects);
	DOREPLIFETIME(UPRItemDefinition, ItemClass);
	
}
