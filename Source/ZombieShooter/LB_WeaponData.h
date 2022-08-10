// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "LB_WeaponData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ZOMBIESHOOTER_API ULB_WeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MagazineSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool FullAuto = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DefaultSpreadAtMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InaccuracyPerShot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* StaticWeaponModel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector WeaponOffset = FVector(26, 15, -5);
};
