// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterClicker/Public/Player/MCPlayerState.h"
#include "UObject/Object.h"
#include "MCUpgradeBase.generated.h"

UENUM(BlueprintType)
enum class EUpgradeRarity : uint8
{
	Common,
	Rare,
	Epic,
	Legendary
};

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class MONSTERCLICKER_API UMCUpgradeBase : public UObject
{
	GENERATED_BODY()
	
public:
	
	virtual void ApplyUpgrade(AMCPlayerState* PlayerState);
	
	bool CanStack() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintGetter, Category="Upgrade")
	EUpgradeRarity GetRarity() const { return Rarity; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintGetter, Category="Upgrade")
	FText GetUpgradeName() const { return UpgradeName; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, BlueprintGetter, Category="Upgrade")
	FText GetUpgradeDescription() const { return Description; }
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Upgrade", BlueprintGetter= GetUpgradeName)
	FText UpgradeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Upgrade", BlueprintGetter= GetUpgradeDescription)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Upgrade", BlueprintGetter= GetRarity)
	EUpgradeRarity Rarity = EUpgradeRarity::Common;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Upgrade")
	int32 MaxStacks = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Upgrade")
	int32 CurrentStacks = 0;
};
