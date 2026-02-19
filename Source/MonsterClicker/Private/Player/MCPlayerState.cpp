// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Player/MCPlayerState.h"

#include "MonsterClicker/Public/Upgrade/MCUpgradeBase.h"

AMCPlayerState::AMCPlayerState()
{
	XP = 0;
	Level = 1;
	XPToNextLevel = 10;
	BaseClickDamage = 1.f;
}

void AMCPlayerState::AddXP(int32 Amount)
{
	XP += Amount;

	while (XP >= XPToNextLevel)
	{
		XP -= XPToNextLevel;
		LevelUp();
	}
}

float AMCPlayerState::GetClickDamage() const
{
	return BaseClickDamage;
}

void AMCPlayerState::AddClickDamage(float Amount)
{
	BaseClickDamage += Amount;
}

void AMCPlayerState::AddUpgrade(UMCUpgradeBase* Upgrade)
{
	if(!Upgrade) return;

	ActiveUpgrades.Add(Upgrade);
	Upgrade->ApplyUpgrade(this);
}

void AMCPlayerState::LevelUp()
{
	Level++;

	CalculateNextLevelXP();

	OnLevelUp.Broadcast(Level);
}

void AMCPlayerState::CalculateNextLevelXP()
{
	XPToNextLevel = FMath::RoundToInt(10.f * FMath::Pow(1.25f, Level - 1));
}
