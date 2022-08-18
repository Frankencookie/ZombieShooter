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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULB_WeaponData* WeaponData;

protected:
	UPROPERTY(BlueprintReadWrite)
	ULB_WeaponComponent* parentWeaponComponent;

public:
	UFUNCTION(BlueprintNativeEvent)
	void Attack();
	UFUNCTION(BlueprintNativeEvent)
	void StopAttack();
	void AltAttack();
	void StopAltAttack();
};
