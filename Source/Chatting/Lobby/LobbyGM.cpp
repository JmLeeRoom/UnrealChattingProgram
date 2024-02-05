// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
	//Player Controller 숫자를 세어서 총 인원를 계산, GameState 저장

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->IncreasePlayerCount();
		GS->OnRep_PlayerCount(); //Only server call
	}
}

void ALobbyGM::Logout(AController* Exiting)
{
	//Player Controller 숫자를 세어서 총 인원를 계산,
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->DecreasePlayerCount();
		GS->OnRep_PlayerCount(); //Only server call
	}


	Super::Logout(Exiting);
}

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->OnRep_PlayerCount(); //Only server call
	}

	FTimerHandle LeftTimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle,
	//	FTimerDelegate::CreateLambda(
	//		[&]() {
	//			if (GS)
	//			{
	//				GS->LeftTime--;
	//				//GS->S2A_UpdateLeftTime(GS->LeftTime);
	//			}
	//		}
	//	), 1.0f, true, -1.0f);

	GetWorld()->GetTimerManager().SetTimer(LeftTimerHandle, this, &ALobbyGM::UpdateLeftTime, 1.0f, true, -1.0f);
}

void ALobbyGM::UpdateLeftTime()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->LeftTime--;
		GS->S2A_UpdateLeftTime(GS->LeftTime);
	}
}
