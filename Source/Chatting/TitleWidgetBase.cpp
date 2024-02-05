// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidgetBase.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	MakeRoomButton = Cast<UButton>(GetWidgetFromName(TEXT("MakeRoomButton")));
	ConnectServerButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectServerButton")));
	IPTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IPTextBox")));

	if (MakeRoomButton)
	{
		MakeRoomButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessMakeRoom);
	}

	if (ConnectServerButton)
	{
		ConnectServerButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ProcessConnectServer);
	}
}

void UTitleWidgetBase::ProcessMakeRoom()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Lobby"), true, TEXT("listen"));
}

void UTitleWidgetBase::ProcessConnectServer()
{
	if (IPTextBox)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(*IPTextBox->GetText().ToString()));
	}
}
