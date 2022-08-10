// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_Character.h"

// Sets default values
ALB_Character::ALB_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();
}

// Called when the game starts or when spawned
void ALB_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALB_Character::Shot()
{

}
