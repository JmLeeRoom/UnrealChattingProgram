// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidgetBase.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "LobbyPC.h"

void ULobbyWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCountTextBox = Cast<UTextBlock>(GetWidgetFromName("PlayerCountTextBox"));
	ChatScrollBox = Cast<UScrollBox>(GetWidgetFromName("ChatScrollBox"));
	ChatInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName("ChatInputTextBox"));
	if (ChatInputTextBox)
	{
		ChatInputTextBox->OnTextChanged.AddDynamic(this, &ULobbyWidgetBase::ProcessChanged);
		ChatInputTextBox->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::ProcessCommitted);
	}

	LeftTimeTextBox = Cast<UTextBlock>(GetWidgetFromName("LeftTimeTextBox"));
}

void ULobbyWidgetBase::ProcessChanged(const FText& Text)
{

}

void ULobbyWidgetBase::ProcessCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());

	if (PC)
	{
		switch (CommitMethod)
		{
		case ETextCommit::OnEnter:
			PC->C2S_SendMessage(ChatInputTextBox->GetText().ToString());
			ChatInputTextBox->SetText(FText::FromString(TEXT("")));
			break;
		case ETextCommit::OnCleared:
			ChatInputTextBox->SetUserFocus(PC);
			break;
		}
	}
}

void ULobbyWidgetBase::UpdatePlayerCount(int32 InPlayerCount)
{
	if (PlayerCountTextBox)
	{
		FString Message = FString::Printf(TEXT("%d 명"), InPlayerCount);
		PlayerCountTextBox->SetText(FText::FromString(Message));
	}
}

void ULobbyWidgetBase::AddMessage(const FString& InMessge)
{
	if (ChatScrollBox)
	{
		UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScrollBox);
		if (NewMessage)
		{
			NewMessage->SetText(FText::FromString(InMessge));
			FSlateFontInfo NewFont = NewMessage->GetFont();
			NewFont.Size = 18;
			NewMessage->SetFont(NewFont);
			ChatScrollBox->AddChild(NewMessage);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

void ULobbyWidgetBase::UpdateLeftTime(int InLeftTime)
{
	if (LeftTimeTextBox)
	{
		if (InLeftTime > 0)
		{
			FString Message = FString::Printf(TEXT("%d초 남음"), InLeftTime);
			LeftTimeTextBox->SetText(FText::FromString(Message));
		}
		else
		{
			LeftTimeTextBox->SetText(FText::FromString(TEXT("시작")));
		}
	}
}

void ULobbyWidgetBase::UpdateHealth(float Health)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Health / 100.0f); // Health가 0에서 100 사이의 값이라고 가정
	}
}

void ULobbyWidgetBase::UpdateBullets(int32 Bullets)
{
	if (BulletsText)
	{
		BulletsText->SetText(FText::AsNumber(Bullets));
	}
}

void ULobbyWidgetBase::UpdateGold(int32 Gold)
{
	if (GoldText)
	{
		GoldText->SetText(FText::AsNumber(Gold));
	}
}
