// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MCUpgradeOptionWidget.generated.h"

class UMCUpgradeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeSelected, UMCUpgradeBase*, SelectedUpgrade);

UCLASS()
class MONSTERCLICKER_API UMCUpgradeOptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitializeOption(UMCUpgradeBase* InUpgrade);

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeSelected OnUpgradeSelected;

protected:
	virtual bool Initialize() override;

	UPROPERTY(meta=(BindWidget))
	UButton* SelectButton;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* UpgradeNameText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DescriptionText;

private:
	UPROPERTY()
	UMCUpgradeBase* Upgrade;

	UFUNCTION()
	void OnButtonClicked();
};
