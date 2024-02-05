// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"


class UTextBlock;
class UScrollBox;
class UEditableTextBox;
class UProgressBar;

/**
 * 
 */
UCLASS()
class CHATTING_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	// UI 요소에 대한 참조
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BulletsText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldText;
public:
	virtual void NativeConstruct() override;

	void UpdatePlayerCount(int32 InPlayerCount);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UTextBlock> PlayerCountTextBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UScrollBox> ChatScrollBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UEditableTextBox> ChatInputTextBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UTextBlock> LeftTimeTextBox;

	UFUNCTION()
	void ProcessChanged(const FText& Text);

	UFUNCTION()
	void ProcessCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void AddMessage(const FString& InMessge);

	void UpdateLeftTime(int InLeftTime);

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float Health);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateBullets(int32 Bullets);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateGold(int32 Gold);
};
