// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LB_ZombieEntrance.h"
#include "LB_EnemyAiController.generated.h"

class LB_StateMachine;
/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API ALB_EnemyAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void Destroyed() override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	ALB_ZombieEntrance* entrance;
	bool isEntrance = false;

	LB_StateMachine* stateMachine;
	bool initted = false;

	void Init();

public:
	void SetEntrance(ALB_ZombieEntrance* newEntrance);
	void GoToEntrance();
	bool HasEntrance();
	void DamageEntrance(int value = 1);
	bool EntranceIntact();

	void ChaseTarget(AActor* target);
};
