// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetBase.generated.h"

class UButton;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CHATTING_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void ProcessMakeRoom();

	UFUNCTION()
	void ProcessConnectServer();


public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<UButton> MakeRoomButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<UButton> ConnectServerButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Components")
	TObjectPtr<UEditableTextBox> IPTextBox;

};
