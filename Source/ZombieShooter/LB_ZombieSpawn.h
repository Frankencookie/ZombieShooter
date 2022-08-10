// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LB_Character.h"
#include "LB_ZombieEntrance.h"
#include "Components/BillboardComponent.h"
#include "LB_EnemyAiController.h"
#include "LB_ZombieSpawn.generated.h"

UCLASS()
class ZOMBIESHOOTER_API ALB_ZombieSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALB_ZombieSpawn();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ALB_Character> CharacterToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<ALB_ZombieEntrance*> Entrypoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBillboardComponent* BillboardSprite;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnZombie();

};
