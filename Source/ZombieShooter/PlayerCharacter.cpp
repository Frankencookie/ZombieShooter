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

	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Socket"));
	WeaponSocket->SetupAttachment(PlayerCamera);

	//WeaponComponent = CreateDefaultSubobject<ULB_WeaponComponent>(TEXT("Weapon Component"));

	WeaponViewmodel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Viewmodel Mesh"));
	WeaponViewmodel->SetupAttachment(WeaponSocket);
}

void APlayerCharacter::BeginPlay()
{
	MovementComponent->MaxWalkSpeed = DefaultSpeed;
	characterInstance = this;

	Super::BeginPlay();
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

	if (SelectedInteractable != nullptr)
	{
		ILB_IInteractable::Execute_Interacted(SelectedInteractable, this);
	}
	else
	{
		GLog->Log("No Interactable");
	}
}

void APlayerCharacter::CheckInteraction()
{
	//Set up Variables
	FHitResult hitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + (PlayerCamera->GetForwardVector() * 200);
	
	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_WorldDynamic, CollisionParameters))
	{
		//Is it valid?
		bool bValid = (hitResult.GetActor() != nullptr);
		if (!bValid)
		{
			return;
		}
		//Interactable?
		bool bInteractable = hitResult.GetActor()->GetClass()->ImplementsInterface(ULB_IInteractable::StaticClass());
		if (bInteractable)
		{
			SelectedInteractable = hitResult.GetActor();
			if (ILB_IInteractable::Execute_GetCanInteract(SelectedInteractable))
			{
				CanInteract();
			}
			else
			{
				SelectedInteractable = nullptr;
			}
		}
		else
		{
			SelectedInteractable = nullptr;
		}
	}
	else
	{
		SelectedInteractable = nullptr;
	}
}

void APlayerCharacter::Attack()
{
	GLog->Log("Trying to fire");
	WeaponComponent->UseWeapon();
	//WeaponComponent->OnUseWeapon.Broadcast();
}

void APlayerCharacter::StopAttack()
{
	WeaponComponent->StopUsingWeapon();
}

void APlayerCharacter::AnimateViewmodel(float DeltaTime)
{
	if (WeaponComponent == nullptr)
	{
		GLog->Log(ELogVerbosity::Error, "No Component");
		return;
	}
	//float WalkDropValue = -GetVelocity().GetAbs().Size() / 40;
	float WalkDropValue = -GetVelocity().GetClampedToSize(-20, 20).GetAbs().Size() / 5;

	//Throw an error if Curve has not been set
	if (IdleSwayCurve == NULL)
	{
		GLog->Log(ELogVerbosity::Error, "NO CURVE DATA");
		return;
	}

	float CurveFinalTime;
	float CurveStartTime;
	IdleSwayCurve->GetTimeRange(CurveStartTime, CurveFinalTime);

	AnimTime += (DeltaTime + (DeltaTime * -WalkDropValue));

	if (AnimTime > CurveFinalTime)
	{
		AnimTime = CurveStartTime;
	}

	FVector SwayValue = IdleSwayCurve->GetVectorValue(AnimTime);
	SwayValue.Z *= (1 + (-WalkDropValue / 10));

	uint32 currentWeaponInt = WeaponComponent->CurrentWeaponInt;

	FVector WeaponOffsetTarget = WeaponComponent->EquippedWeapons[currentWeaponInt]->WeaponData->WeaponOffset;

	//Jumping
	if (!GetCharacterMovement()->IsMovingOnGround())
	{
		WeaponOffsetTarget.Z += -JumpWeaponOffset;
		SwayValue.Z = 0;
		SwayValue.Y = 0;
	}

	//Add Side Input
	WeaponOffsetTarget.Y += GetInputAxisValue("Right") * HorizontalOffsetMultiplier;

	//WeaponOffsetFinal = WeaponOffsetTarget;
	WeaponOffsetBlend = FMath::VInterpTo(WeaponOffsetBlend, WeaponOffsetTarget, DeltaTime, OffsetSpeed);

	//Offset Value Addition
	WeaponOffsetFinal = WeaponOffsetBlend;
	WeaponOffsetFinal += SwayValue * (SwayBase + -WalkDropValue / SwayMultiplier);

	/*
	//Blend X axis recoil
	RecoilXTarget = FMath::VInterpTo(RecoilXTarget, FVector(0, 0, 0), DeltaTime, CurrentWeaponInfo->RecoilSpeed);
	//Recoil Z Blend
	RecoilZTarget = FMath::VInterpTo(RecoilZTarget, FVector(0, 0, 0), DeltaTime, CurrentWeaponInfo->RecoilSpeed / 4);
	RecoilZBlend = FMath::VInterpTo(RecoilZBlend, RecoilZTarget, DeltaTime, CurrentWeaponInfo->RecoilSpeed / 2);

	//Add to OffsetValue
	WeaponOffsetFinal += RecoilXTarget;
	WeaponOffsetFinal += RecoilZBlend;

	*/
	FVector WeaponOffsetFinalFinal = FMath::Lerp(WeaponSocket->GetRelativeLocation(), WeaponOffsetFinal, DeltaTime * 10);

	//Set Position
	WeaponSocket->SetRelativeLocation(WeaponOffsetFinalFinal);
	//SkeletalViewModel->SetRelativeLocation(WeaponOffsetFinal);

	//Rotation
	FRotator RotationOffsetTarget = FRotator(0, 0, 0);
	RotationOffsetTarget.Pitch = -GetInputAxisValue("LookUp") * RotMultiplier;
	RotationOffsetTarget.Yaw = GetInputAxisValue("LookRight") * RotMultiplier;
	RotationOffset = FMath::RInterpTo(RotationOffset, RotationOffsetTarget, DeltaTime, RotInterpSpeed);

	//Recoil Rotation
	//RecoilRotationTarget = FMath::RInterpTo(RecoilRotationTarget, FRotator(0, 0, 0), DeltaTime, WeaponComponent->CurrentWeaponData->RecoilSpeed);
	//FRotator RecoilRotBlend = FRotator(0, 0, 0);
	//RecoilRotBlend = FMath::RInterpTo(RecoilRotBlend, RecoilRotationTarget, DeltaTime, CurrentWeaponInfo->RecoilSpeed);

	//RotationOffset += RecoilRotBlend;

	//Set Rotation
	WeaponSocket->SetRelativeRotation(RotationOffset);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TiltCamera(DeltaTime);
	AnimateViewmodel(DeltaTime);
	CheckInteraction();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
}
