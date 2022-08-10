// Fill out your copyright notice in the Description page of Project Settings.


#include "LB_StateMachine.h"

LB_StateMachine::LB_StateMachine()
{
}

LB_StateMachine::~LB_StateMachine()
{

}

void LB_StateMachine::Init(LB_State* startState, ALB_EnemyAiController* aiController, UWorld* worldPtr)
{
	parentController = aiController;
	worldRef = worldPtr;
	ChangeState(startState);
	initted = true;
	secondFrame = true;
}

void LB_StateMachine::UpdateState(float DeltaTime)
{
	if (currentState != nullptr && initted)
	{
		if (secondFrame)
		{
			currentState->StateSecondFrame();
			secondFrame = false;
		}
		currentState->StateUpdate(DeltaTime);
	}
}

void LB_StateMachine::ChangeState(LB_State* newState, bool callExit, bool skipDestroy)
{
	GLog->Log("Changing state");
	if (initted && !skipDestroy)
	{
		GLog->Log("State Wasn't null");
		if (callExit)
		{
			currentState->StateExit();
		}

		delete currentState;
		currentState = NULL;
	}

	currentState = newState;
	currentState->InitState(this, parentController, worldRef);
	currentState->StateBegin();
}

LB_State::LB_State()
{
}

void LB_State::InitState(LB_StateMachine* parent, ALB_EnemyAiController* aiController, UWorld* worldPtr)
{
	parentSM = parent;
	parentAiController = aiController;
	worldRef = worldPtr;
}

void LB_State::StateBegin()
{
}

void LB_State::StateSecondFrame()
{
}

void LB_State::StateUpdate(float DeltaTime)
{
}

void LB_State::StateExit()
{
}
