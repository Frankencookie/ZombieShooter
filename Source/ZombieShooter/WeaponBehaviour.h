// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LB_WeaponData.h"
#include "WeaponBehaviour.generated.h"

class ULB_WeaponComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class ZOMBIESHOOTER_API UWeaponBehaviour : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Init(ULB_WeaponComponent* parent);

	void NativeUpdateWeapon(float delta);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateWeapon(float delta);

	UFUNCTION(BlueprintCallable)
	bool CalculateCanFire(float delta);

	void RateOfFireControl(float delta);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULB_WeaponData* WeaponData;

protected:
	UPROPERTY(BlueprintReadWrite)
	ULB_WeaponComponent* parentWeaponComponent;

	//Weapon Params
	UPROPERTY(BlueprintReadOnly)
	int CurrentMagAmmo;
	UPROPERTY(BlueprintReadOnly)
	int CurrentStoredAmmo;

	float timeSinceLastShot = 0;
	bool canFire = true;

	bool triggerDown = false;
	bool firedSinceTriggerDown = false;
	bool canShootTime = false;

public:
	//NATIVE STUFF
	void NativeAttack();
	void NativeStopAttack();


	//BLUEPRINT STUFF
	UFUNCTION(BlueprintImplementableEvent)
	void Attack();
	UFUNCTION(BlueprintImplementableEvent)
	void StopAttack();
	void AltAttack();
	void StopAltAttack();

	//UFUNCTION(BlueprintNativeEvent)
	//void Reload();
};
