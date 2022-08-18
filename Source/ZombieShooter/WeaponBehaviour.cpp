// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBehaviour.h"
#include "LB_WeaponComponent.h"

void UWeaponBehaviour::Init(ULB_WeaponComponent* parent)
{
	parentWeaponComponent = parent;
}

void UWeaponBehaviour::Attack_Implementation()
{
	if (parentWeaponComponent != nullptr)
	{
		parentWeaponComponent->ShootRaycast();
	}
}

void UWeaponBehaviour::StopAttack_Implementation()
{

}