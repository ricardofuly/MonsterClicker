// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCUpgradeBase.h"
#include "UObject/Object.h"
#include "MCUpgradeManager.generated.h"

class AMCPlayerState;
class UMCUpgradeBase;

UCLASS(Blueprintable)
class MONSTERCLICKER_API UMCUpgradeManager : public UObject
{
	GENERATED_BODY()
	
public:
	
	void Initialize(AMCPlayerState* InPlayerState);
	
	UFUNCTION(BlueprintCallable)
	TArray<UMCUpgradeBase*> GetUpgradeChoices(int32 Count = 3);
	
protected:
	
	// Pool de upgrades possíveis
	UPROPERTY(EditDefaultsOnly, Instanced, Category="Upgrades")
	TArray<UMCUpgradeBase*> UpgradePool;

	UPROPERTY()
	AMCPlayerState* PlayerState;

	// Internos
	UMCUpgradeBase* GetRandomUpgrade() const;
	float GetRarityWeight(EUpgradeRarity Rarity) const;
};
