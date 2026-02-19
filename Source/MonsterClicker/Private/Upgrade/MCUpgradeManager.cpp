// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Upgrade/MCUpgradeManager.h"

void UMCUpgradeManager::Initialize(AMCPlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
}

TArray<UMCUpgradeBase*> UMCUpgradeManager::GetUpgradeChoices(int32 Count)
{
	TArray<UMCUpgradeBase*> Result;

	if (!PlayerState || UpgradePool.Num() == 0)
		return Result;

	int32 Safety = 0;

	while (Result.Num() < Count && Safety < 100)
	{
		Safety++;

		UMCUpgradeBase* Upgrade = GetRandomUpgrade();
		if (!Upgrade)
			continue;

		if (Result.Contains(Upgrade))
			continue;

		if (!Upgrade->CanStack())
			continue;

		Result.Add(Upgrade);
	}

	return Result;
}

UMCUpgradeBase* UMCUpgradeManager::GetRandomUpgrade() const
{
	float TotalWeight = 0.f;

	for (UMCUpgradeBase* Upgrade : UpgradePool)
	{
		if (!Upgrade || !Upgrade->CanStack())
			continue;

		TotalWeight += GetRarityWeight(Upgrade->GetRarity());
	}

	if (TotalWeight <= 0.f)
		return nullptr;

	float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Accumulated = 0.f;

	for (UMCUpgradeBase* Upgrade : UpgradePool)
	{
		if (!Upgrade || !Upgrade->CanStack())
			continue;

		Accumulated += GetRarityWeight(Upgrade->GetRarity());

		if (Roll <= Accumulated)
		{
			return Upgrade;
		}
	}

	return nullptr;
}

float UMCUpgradeManager::GetRarityWeight(EUpgradeRarity Rarity) const
{
	switch (Rarity)
	{
	case EUpgradeRarity::Common:     return 60.f;
	case EUpgradeRarity::Rare:       return 25.f;
	case EUpgradeRarity::Epic:       return 10.f;
	case EUpgradeRarity::Legendary:  return 5.f;
	default:                         return 1.f;
	}
}
