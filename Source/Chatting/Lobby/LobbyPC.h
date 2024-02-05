// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

class ULobbyWidgetBase;
/**
 * 
 */
UCLASS()
class CHATTING_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TObjectPtr<ULobbyWidgetBase> LobbyWidgetObject;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	//TSubclassOf<ULobbyWidgetBase> LobbyWidgetClass;
	

	UFUNCTION(Server, Unreliable, WithValidation)
	void C2S_SendMessage(const FString& InMessage); //client call
	bool C2S_SendMessage_Validate(const FString& InMessage);
	void C2S_SendMessage_Implementation(const FString& InMessage); //server execute

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FString& InMessage); //Server Call
	void S2C_SendMessage_Implementation(const FString& InMessage); //client execute
};
