// Fill out your copyright notice in the Description page of Project Settings.


#include "Datas/PRUpgradeData.h"
#include "Net/UnrealNetwork.h"

void UPRUpgradeData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPRUpgradeData, DisplayName);
	DOREPLIFETIME(UPRUpgradeData, Description);
	DOREPLIFETIME(UPRUpgradeData, Icon);
	DOREPLIFETIME(UPRUpgradeData, Rarity);
	DOREPLIFETIME(UPRUpgradeData, UpgradeLevel);
	DOREPLIFETIME(UPRUpgradeData, Effects);
	DOREPLIFETIME(UPRUpgradeData, SourceItemDefinition);

}
