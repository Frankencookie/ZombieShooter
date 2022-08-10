// Fill out your copyright notice in the Description page of Project Settings.

#include "LB_EnemyAiController.h"
#include "ZombieStates.h"
#include "LB_StateMachine.h"

void ALB_EnemyAiController::BeginPlay()
{
	Super::BeginPlay();
}

void ALB_EnemyAiController::Tick(float DeltaTime)
{
	//MoveToLocation(FVector(700, -180, 0));
	if (initted)
	{
		stateMachine->UpdateState(DeltaTime);
	}
	else
	{
		Init();
	}

}

void ALB_EnemyAiController::Destroyed()
{
	delete stateMachine;
}

void ALB_EnemyAiController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (isEntrance)
	{
		stateMachine->ChangeState(new ZombieBreakEntranceState());
	}
}

void ALB_EnemyAiController::Init()
{
	GLog->Log("Spawned");
	stateMachine = new LB_StateMachine();
	GLog->Log("State Machine Created");
	if (HasEntrance())
	{
		stateMachine->Init(new ZombieSpawnedState(), this, GetWorld());
	}
	else
	{

	}
	GLog->Log("State machine initted");
	initted = true;
}

void ALB_EnemyAiController::SetEntrance(ALB_ZombieEntrance* newEntrance)
{
	entrance = newEntrance;
	isEntrance = true;
}

void ALB_EnemyAiController::GoToEntrance()
{
	if (isEntrance)
	{
		GLog->Log("Entrance found, going there");
		MoveToLocation(entrance->EntrancePoint->GetComponentLocation());
	}
}

bool ALB_EnemyAiController::HasEntrance()
{
	return isEntrance;
}

void ALB_EnemyAiController::DamageEntrance(int value)
{
	if (isEntrance)
	{
		entrance->DamageEntrance(value);
	}
}

bool ALB_EnemyAiController::EntranceIntact()
{
	return !entrance->GetDestroyed();
}

void ALB_EnemyAiController::ChaseTarget(AActor* target)
{
	MoveToActor(target);
}
