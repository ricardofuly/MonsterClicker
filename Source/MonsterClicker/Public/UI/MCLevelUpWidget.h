// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterClicker/Public/Upgrade/MCUpgradeBase.h"
#include "MCLevelUpWidget.generated.h"


class UHorizontalBox;
class UMCUpgradeOptionWidget;
/**
 * 
 */
UCLASS()
class MONSTERCLICKER_API UMCLevelUpWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitializeLevelUp(const TArray<UMCUpgradeBase*>& UpgradeChoices);

protected:
	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* OptionsContainer;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMCUpgradeOptionWidget> OptionWidgetClass;

private:
	UFUNCTION()
	void HandleUpgradeSelected(UMCUpgradeBase* SelectedUpgrade);
};
