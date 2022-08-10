// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieStates.h"
#include "LB_EnemyAiController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

//Spawned state
#pragma region SpawnedState

void ZombieSpawnedState::StateBegin()
{
	parentAiController->GoToEntrance();
}

#pragma endregion

//Chase player state
#pragma region ChaseState

void ZombieChaseState::StateBegin()
{
	target = (ALB_Character*)UGameplayStatics::GetPlayerCharacter(worldRef, 0);
}

void ZombieChaseState::StateUpdate(float DeltaTime)
{
	parentAiController->ChaseTarget(target);
}

void ZombieChaseState::StateExit()
{
}

#pragma endregion

void ZombieBreakEntranceState::StateBegin()
{
	GLog->Log("Breaking Entrance");
}

void ZombieBreakEntranceState::StateUpdate(float DeltaTime)
{
	currentTime += DeltaTime;
	if (currentTime > damageTime)
	{
		if (parentAiController->EntranceIntact())
		{
			parentAiController->DamageEntrance();
			currentTime = 0;
		}
		else
		{
			parentSM->ChangeState(new ZombieChaseState());
		}
	}
}
