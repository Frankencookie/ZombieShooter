// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LB_Character.h"
#include "Camera/CameraComponent.h"
#include "Curves/CurveVector.h"
#include "LB_WeaponComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LB_IInteractable.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API APlayerCharacter : public ALB_Character
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	static APlayerCharacter* characterInstance;

	//Camera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Stuff")
	UCameraComponent* PlayerCamera;

	//WeaponComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULB_WeaponComponent* WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponViewmodel;


protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float DefaultSpeed = 300;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float SprintSpeed = 500;

	//LookSpeed
	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float LookSensitivityX = 1;
	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float LookSensitivityY = 1;

	//Current Camera Rotation
	float CameraY = 0;

	//Camera Tilt
	float TiltTarget = 0;

	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float TiltMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float TiltSpeed = 0.5f;

	float currentCamTilt = 0;

	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float MinCameraAngle = -60;

	UPROPERTY(EditAnywhere, Category = "Camera Stuff")
	float MaxCameraAngle = 60;

	//HeadSocket
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Stuff")
	USceneComponent* CameraSocket;

	//Movement
	void MoveForward(float value);
	void MoveRight(float value);
	void Sprint();
	void StopSprint();

	//HeadLook
	void LookUp(float value);
	void LookRight(float value);

	void TiltCamera(float delta);

	//Interaction
	void Interact();
	void CheckInteraction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintCosmetic)
	void CanInteract();

	AActor* SelectedInteractable = nullptr;

	//Weapon Stuff
	UFUNCTION(BlueprintCallable)
	void Attack();
	void StopAttack();

#pragma region ViewmodelAnimation

	UPROPERTY(EditAnywhere)
	USceneComponent* WeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewmodel Sway")
	UCurveVector* IdleSwayCurve;

	void AnimateViewmodel(float DeltaTime);

	//Smooth Position blend
	FVector WeaponOffsetBlend = FVector(0, 0, 0);
	FVector WeaponOffsetFinal = FVector(0, 0, 0);
	float AnimTime = 0;
	float OffsetSpeed = 10;
	float SwayBase = 1;
	float SwayMultiplier = 3;

	float HorizontalOffsetMultiplier = 3;

	//Smooth Rotation
	FRotator RotationOffset = FRotator(0, 0, 0);
	float RotInterpSpeed = 5;
	float RotMultiplier = 3;

	UPROPERTY(EditAnywhere)
	float JumpWeaponOffset = 8;

#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractRange = 100.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
