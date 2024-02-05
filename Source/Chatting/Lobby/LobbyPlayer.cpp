// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayer.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LobbyPC.h"
// Sets default values
ALobbyPlayer::ALobbyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	FirstPersonCamera->bUsePawnControlRotation = true;
	FirstPersonCamera->SetupAttachment(GetMesh(), FName("head"));
}

// Called when the game starts or when spawned
void ALobbyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ALobbyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALobbyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	const ALobbyPC* PlayerController = Cast<ALobbyPC>(GetController());

	if (EnhancedPlayerInputComponent == nullptr || PlayerController == nullptr)
	{
		return;
	}
	
	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if(EnhancedSubsystem == nullptr)
	{
		return;
	}

	EnhancedSubsystem->AddMappingContext(InputMappingContext, 1);

	EnhancedPlayerInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ALobbyPlayer::Move);
	EnhancedPlayerInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ALobbyPlayer::Look);
	EnhancedPlayerInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedPlayerInputComponent->BindAction(FireInputAction, ETriggerEvent::Started, this, &ALobbyPlayer::StartFire);
	EnhancedPlayerInputComponent->BindAction(FireInputAction, ETriggerEvent::Completed, this, &ALobbyPlayer::StopFire);
}
void ALobbyPlayer::Move(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	if(InputValue.X != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("up down"));
		AddMovementInput(GetActorRightVector(), InputValue.X);
		
	}

	if(InputValue.Y != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("left right"));
		AddMovementInput(GetActorForwardVector(), InputValue.Y);	
	}
	
}

void ALobbyPlayer::Look(const FInputActionValue& Value)
{
	const FVector2D InputValue = Value.Get<FVector2D>();

	if(InputValue.X != 0.0f)
	{
		AddControllerYawInput(InputValue.X);
	}

	if(InputValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputValue.Y);	
	}
}

void ALobbyPlayer::StartFire(const FInputActionValue& Value)
{
	Fire();
}

void ALobbyPlayer::StopFire(const FInputActionValue& Value)
{
}
void ALobbyPlayer::Fire()
{
	if (HasAuthority()) {
		PerformLineTrace();
	} else {
		ServerFire();
	}
}

bool ALobbyPlayer::ServerFire_Validate()
{
	return true;
}

void ALobbyPlayer::ServerFire_Implementation()
{
	PerformLineTrace();
}

void ALobbyPlayer::PerformLineTrace()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신은 무시
	QueryParams.bTraceComplex = true;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		AActor* HitActor = HitResult.GetActor();
	}
	
	if (GetWorld())
	{
		DrawDebugLine(GetWorld(),EyeLocation,TraceEnd,FColor::Red,false,1.0f, 0, 1.0f);
	}
	
}

