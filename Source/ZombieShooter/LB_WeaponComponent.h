// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "LB_IShootable.h"
#include "LB_WeaponData.h"
#include "LB_WeaponComponent.generated.h"

class APlayerCharacter;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZOMBIESHOOTER_API ULB_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULB_WeaponComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULB_WeaponData* CurrentWeaponData;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	APlayerCharacter* owner;

	UPROPERTY(EditAnywhere)
	float range = 2000;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UseWeapon();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopUsingWeapon();

	void ShootRaycast(float spread = 0);
};
