// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Upgrade/MCUpgrade_ClickDamage.h"

void UMCUpgrade_ClickDamage::ApplyUpgrade(AMCPlayerState* PlayerState)
{
	if (!CanStack())
		return;

	Super::ApplyUpgrade(PlayerState);

	PlayerState->AddClickDamage(DamageIncrease);
}
