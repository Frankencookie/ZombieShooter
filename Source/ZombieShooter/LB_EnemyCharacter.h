// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LB_Character.h"
#include "LB_StateMachine.h"
#include "LB_EnemyAiController.h"
#include "LB_EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API ALB_EnemyCharacter : public ALB_Character
{
	GENERATED_BODY()
	
public:
	ALB_EnemyCharacter();

protected:
	ALB_EnemyAiController* aiController;
};
