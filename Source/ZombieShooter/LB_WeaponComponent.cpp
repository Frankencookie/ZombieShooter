// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_WeaponComponent.h"
#include "WeaponBehaviour.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
ULB_WeaponComponent::ULB_WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULB_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	owner = Cast<APlayerCharacter>(GetOwner());
	if (owner == nullptr)
	{
		GLog->Log("Player Not Found");
	}
	GLog->Log("Begin play called in code");

	
}

void ULB_WeaponComponent::UseWeapon()
{
	if (currentWeapon != nullptr)
	{
		currentWeapon->NativeAttack();
	}
}

void ULB_WeaponComponent::StopUsingWeapon()
{
	if (currentWeapon != nullptr)
	{
		currentWeapon->NativeStopAttack();
	}
}


// Called every frame
void ULB_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (currentWeapon != nullptr)
	{
		currentWeapon->NativeUpdateWeapon(DeltaTime);
	}
	// ...
}

void ULB_WeaponComponent::ShootRaycast(float spread)
{
	if (owner == nullptr)
	{
		return;
	}
	FHitResult hitResult;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(owner);
	FVector startPos = owner->PlayerCamera->GetComponentLocation();
	FVector endPos = owner->PlayerCamera->GetForwardVector() * range;
	endPos = endPos + startPos;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, startPos, endPos, ECC_WorldDynamic, CollisionParameters))
	{
		GLog->Log("Hit Something");
		//Is it valid?
		bool bValid = (hitResult.GetActor() != nullptr);
		if (!bValid)
		{
			return;
		}
		//Is it shootable?
		bool bInteractable = hitResult.Actor->GetClass()->ImplementsInterface(ULB_IShootable::StaticClass());

		if (bInteractable)
		{
			GLog->Log("Shootable, Damaging");
			ILB_IShootable::Execute_Shot(hitResult.GetActor());
		}
	}
}

