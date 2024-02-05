// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyWidgetBase.h"

void ALobbyGS::IncreasePlayerCount()
{
	PlayerCount++;
	UE_LOG(LogTemp, Warning, TEXT("PlayerCount %d"), PlayerCount);
}

void ALobbyGS::DecreasePlayerCount()
{
	PlayerCount--;
	UE_LOG(LogTemp, Warning, TEXT("PlayerCount %d"), PlayerCount);
}

//Server »©°í ½ÇÇà
void ALobbyGS::OnRep_PlayerCount()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->LobbyWidgetObject)
	{
		//UI Update
		PC->LobbyWidgetObject->UpdatePlayerCount(PlayerCount);
	}
}

void ALobbyGS::S2A_UpdateLeftTime_Implementation(int InLeftTime)
{
	LeftTime = InLeftTime;

	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->LobbyWidgetObject)
	{
		//UI Update
		PC->LobbyWidgetObject->UpdateLeftTime(LeftTime);
	}
}

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALobbyGS, PlayerCount);
	//DOREPLIFETIME_CONDITION(ALobbyGS, PlayerCount, COND_InitialOnly)
}
