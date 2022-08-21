// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBehaviour.h"
#include "LB_WeaponComponent.h"

void UWeaponBehaviour::Init(ULB_WeaponComponent* parent)
{
	parentWeaponComponent = parent;
	CurrentMagAmmo = WeaponData->MagazineSize;
	CurrentStoredAmmo = WeaponData->MaxAmmo;
}

void UWeaponBehaviour::NativeUpdateWeapon(float delta)
{
	RateOfFireControl(delta);
	CalculateCanFire(delta);
	if (canFire && triggerDown)
	{
		firedSinceTriggerDown = true;
		timeSinceLastShot = 0;
		canShootTime = false;
		Attack();
	}
	UpdateWeapon(delta);
}

void UWeaponBehaviour::UpdateWeapon_Implementation(float delta)
{

}

bool UWeaponBehaviour::CalculateCanFire(float delta)
{
	if (!canShootTime)
	{
		canFire = false;
		return false;
	}
	//Have enough ammo?
	if (CurrentMagAmmo < 1)
	{
		canFire = false;
		return false;
	}
	//Fired but trigger is still down and semi-auto
	if (!WeaponData->FullAuto && firedSinceTriggerDown)
	{
		canFire = false;
		return false;
	}
	canFire = true;
	return true;
}

void UWeaponBehaviour::RateOfFireControl(float delta)
{
	if (!canShootTime)
	{
		timeSinceLastShot += delta;
		canShootTime = timeSinceLastShot > WeaponData->DelayBetweenShots;
	}
}

void UWeaponBehaviour::NativeAttack()
{
	triggerDown = true;
}

void UWeaponBehaviour::NativeStopAttack()
{
	triggerDown = false;
	if (firedSinceTriggerDown)
	{
		firedSinceTriggerDown = false;
		StopAttack();
	}
}
