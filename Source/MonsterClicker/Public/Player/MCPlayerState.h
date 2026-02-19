// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MCPlayerState.generated.h"

class UMCUpgradeBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpSignature, int32, NewLevel);

UCLASS()
class MONSTERCLICKER_API AMCPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMCPlayerState();
	
	void AddXP(int32 Amount);
	
	int32 GetXP() const { return XP; }
	int32 GetCurrentLevel() const { return Level; }
	int32 GetXPToNextLevel() const { return XPToNextLevel; }
	
	float GetClickDamage() const;
	
	void AddClickDamage(float Amount);

	// Upgrade
	void AddUpgrade(UMCUpgradeBase* Upgrade);

	UPROPERTY(BlueprintAssignable)
	FOnLevelUpSignature OnLevelUp;
	
protected:
	
	UPROPERTY(VisibleAnywhere)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	int32 XPToNextLevel = 10;

	UPROPERTY(VisibleAnywhere)
	float BaseClickDamage = 1.f;

	UPROPERTY()
	TArray<UMCUpgradeBase*> ActiveUpgrades;

	void LevelUp();
	void CalculateNextLevelXP();
};
