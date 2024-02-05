// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidgetBase.h"


void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;

	FSoftClassPath LobbyWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/Lobby/WBP_Lobby.WBP_Lobby_C'"));
	UClass* WidgetClass = LobbyWidgetClass.TryLoadClass<UUserWidget>();

	if (WidgetClass && IsLocalPlayerController())
	{
		LobbyWidgetObject = CreateWidget<ULobbyWidgetBase>(this, WidgetClass);
		if (LobbyWidgetObject)
		{
			LobbyWidgetObject->AddToViewport();
			//LobbyWidgetObject->RemoveFromViewport();
		}
	}
}

bool ALobbyPC::C2S_SendMessage_Validate(const FString& InMessage)
{
	return true;
}

void ALobbyPC::C2S_SendMessage_Implementation(const FString& InMessage)
{
	for (auto It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	//for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		ALobbyPC* PC =  Cast<ALobbyPC>(*It);
		if (PC)
		{
			PC->S2C_SendMessage(InMessage);
		}
	}
}

//execute client
void ALobbyPC::S2C_SendMessage_Implementation(const FString& InMessage)
{
	if (LobbyWidgetObject)
	{
		LobbyWidgetObject->AddMessage(InMessage);
	}
}
