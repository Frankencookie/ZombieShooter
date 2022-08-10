// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_ZombieSpawn.h"

// Sets default values
ALB_ZombieSpawn::ALB_ZombieSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	BillboardSprite = CreateDefaultSubobject<UBillboardComponent>("Editor Sprite");
	BillboardSprite->SetupAttachment(RootComponent);

	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void ALB_ZombieSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALB_ZombieSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALB_ZombieSpawn::SpawnZombie()
{
	FActorSpawnParameters SpawnParams;
	ALB_Character* newCharacter = (ALB_Character*)GetWorld()->SpawnActor<ALB_Character>(CharacterToSpawn, GetActorTransform(), SpawnParams);
	ALB_EnemyAiController* controller = Cast<ALB_EnemyAiController>(newCharacter->GetController());
	if (Entrypoints.Num() > 0)
	{
		GLog->Log("Entrypoint Set");
		controller->SetEntrance(Entrypoints[0]);
	}
	else
	{
		GLog->Log("No Entrypoints defined");
	}
}

