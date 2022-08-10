// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "LB_ZombieEntrance.generated.h"


UCLASS()
class ZOMBIESHOOTER_API ALB_ZombieEntrance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALB_ZombieEntrance();

	UPROPERTY(EditAnywhere)
	USceneComponent* EntrancePoint;
	UPROPERTY(EditAnywhere)
	USceneComponent* ExitPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBillboardComponent* BillboardSprite;
	UPROPERTY(EditAnywhere)
	int hitpoints = 3;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool GetDestroyed();

	UFUNCTION(BlueprintCallable)
	int GetHitpoints();

	void DamageEntrance(int amount = 1);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EntranceDamaged(int amount);
};
