// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LobbyPlayer.generated.h"

class UCameraComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
UCLASS()
class CHATTING_API ALobbyPlayer : public ACharacter
{
	GENERATED_BODY()
protected:
	// 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="FPSCamera")
	UCameraComponent* FirstPersonCamera;
	// 키입력
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* FireInputAction;
public:
	// Sets default values for this character's properties
	ALobbyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartFire(const FInputActionValue& Value);
	void StopFire(const FInputActionValue& Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	// 서버에서 실행될 발사 로직
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();
	bool ServerFire_Validate();
	void ServerFire_Implementation();
protected:

	// 실제 라인 트레이스를 수행하는 함수
	void PerformLineTrace();	

};
