// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LB_StateMachine.h"
#include "CoreMinimal.h"

class ALB_Character;

class ZombieSpawnedState : public LB_State
{
public:
	void StateBegin() override;
};

class ZombieChaseState : public LB_State
{
public:
	void StateBegin() override;
	void StateUpdate(float DeltaTime) override;
	void StateExit() override;

protected:
	ALB_Character* target;
};

class ZombieBreakEntranceState : public LB_State
{
public:
	void StateBegin() override;
	void StateUpdate(float DeltaTime) override;

private:
	float currentTime = 0;
	float damageTime = 2;
};