// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class LB_State;
class ALB_EnemyAiController;

/**
 * 
 */
class ZOMBIESHOOTER_API LB_StateMachine
{
public:
	LB_StateMachine();
	~LB_StateMachine();

	void Init(LB_State* startState, ALB_EnemyAiController* aiController, UWorld* worldPtr);

	void UpdateState(float DeltaTime);

	void ChangeState(LB_State* newState, bool callExit = true, bool skipDestroy = false);

protected:
	LB_State* currentState;
	ALB_EnemyAiController* parentController;
	bool initted = false;
	bool secondFrame = false;
	UWorld* worldRef;
};

class LB_State
{
public:
	LB_State();
protected:
	LB_StateMachine* parentSM;
	ALB_EnemyAiController* parentAiController;
	UWorld* worldRef;

public:
	void InitState(LB_StateMachine* parent, ALB_EnemyAiController* aiController, UWorld* worldPtr);
	virtual void StateBegin();
	virtual void StateSecondFrame();
	virtual void StateUpdate(float DeltaTime);
	virtual void StateExit();
};