// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter* APlayerCharacter::characterInstance;

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Socket"));
	CameraSocket->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(CameraSocket);
	CameraSocket->SetRelativeLocation(FVector(0, 0, 50.0f));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->MaxWalkSpeed = DefaultSpeed;
	characterInstance = this;
}

void APlayerCharacter::MoveForward(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}

	TiltTarget = value * TiltMultiplier;
}

void APlayerCharacter::Sprint()
{
	MovementComponent->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint()
{
	MovementComponent->MaxWalkSpeed = DefaultSpeed;
}

void APlayerCharacter::LookUp(float value)
{
	CameraY += -value * LookSensitivityY;
	CameraY = FMath::Clamp(CameraY, MinCameraAngle, MaxCameraAngle);
	CameraSocket->SetRelativeRotation(FRotator(CameraY, 0, 0));

	//AddControllerPitchInput(value * LookSensitivityX);
}

void APlayerCharacter::LookRight(float value)
{
	AddControllerYawInput(value * LookSensitivityX);
}

void APlayerCharacter::TiltCamera(float delta)
{
	currentCamTilt = FMath::FInterpTo(currentCamTilt, TiltTarget, delta, TiltSpeed);
	PlayerCamera->SetRelativeRotation(FRotator(0, 0, currentCamTilt));
}

void APlayerCharacter::Interact()
{
	GLog->Log("Interact Pressed");

	//Set up Variables
	FHitResult hitBoi;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + (PlayerCamera->GetForwardVector() * 200);

	if (GetWorld()->LineTraceSingleByChannel(hitBoi, Start, End, ECC_WorldDynamic, CollisionParameters))
	{
		GLog->Log("Hit Something");
		//Is it interactable?
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiltCamera(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
}
