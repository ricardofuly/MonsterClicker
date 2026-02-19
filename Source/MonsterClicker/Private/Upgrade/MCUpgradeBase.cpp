// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Upgrade/MCUpgradeBase.h"

void UMCUpgradeBase::ApplyUpgrade(AMCPlayerState* PlayerState)
{
	if (!PlayerState)
		return;

	if (!CanStack())
		return;

	CurrentStacks++;
}

bool UMCUpgradeBase::CanStack() const
{
	return CurrentStacks < MaxStacks;
}
