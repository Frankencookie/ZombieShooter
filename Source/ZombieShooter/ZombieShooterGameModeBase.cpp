// Copyright Epic Games, Inc. All Rights Reserved.


#include "ZombieShooterGameModeBase.h"

AZombieShooterGameModeBase::AZombieShooterGameModeBase()
{
	
}

bool AZombieShooterGameModeBase::SetGamerule(FString rule, bool value)
{
	if (!GameRules.Contains(rule))
	{
		GLog->Log("Gamerule not found");
		return false;
	}
	GameRules.Add(rule, value);
	return true;
}

bool AZombieShooterGameModeBase::GetGamerule(FString rule)
{
	if (!GameRules.Contains(rule))
	{
		GLog->Log("Gamerule not found");
		return false;
	}
	return GameRules.FindChecked(rule);
}
