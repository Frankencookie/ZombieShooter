// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIESHOOTER_API AZombieShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AZombieShooterGameModeBase();


	//GAMERULES
	UPROPERTY(EditAnywhere)
	TMap<FString, bool> GameRules = 
	{
		{"bInfiniteAmmo", false},
		{"bGodMode", false},
		{"bZombieInstakill", false},
		{"bPlayerInstakill", false},
		{"bFriendlyFire", false},
		{"bUnlimitedPoints", false}
	};

	UFUNCTION(BlueprintCallable)
	bool SetGamerule(FString rule, bool value);
	UFUNCTION(BlueprintCallable)
	bool GetGamerule(FString rule);
};
