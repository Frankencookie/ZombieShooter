// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_ZombieEntrance.h"


// Sets default values
ALB_ZombieEntrance::ALB_ZombieEntrance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	EntrancePoint = CreateDefaultSubobject<USceneComponent>("Entrypoint");
	ExitPoint = CreateDefaultSubobject<USceneComponent>("Exitpoint");

	EntrancePoint->SetupAttachment(RootComponent);
	ExitPoint->SetupAttachment(RootComponent);

	BillboardSprite = CreateDefaultSubobject<UBillboardComponent>("Editor Sprite");
	BillboardSprite->SetupAttachment(RootComponent);

	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ALB_ZombieEntrance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALB_ZombieEntrance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALB_ZombieEntrance::GetDestroyed()
{
	return hitpoints <= 0;
}

int ALB_ZombieEntrance::GetHitpoints()
{
	return hitpoints;
}

void ALB_ZombieEntrance::DamageEntrance(int amount)
{
	hitpoints = hitpoints - amount;
	EntranceDamaged(amount);
}

