// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCUpgradeBase.h"
#include "MCUpgrade_ClickDamage.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERCLICKER_API UMCUpgrade_ClickDamage : public UMCUpgradeBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, Category= "Upgrade")
	float DamageIncrease = 1.f;
	
	virtual void ApplyUpgrade(AMCPlayerState* PlayerState) override;
};
