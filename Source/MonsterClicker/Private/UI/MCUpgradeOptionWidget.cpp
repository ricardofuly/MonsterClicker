// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/UI/MCUpgradeOptionWidget.h"

#include "MonsterClicker/Public/Upgrade/MCUpgradeBase.h"

void UMCUpgradeOptionWidget::InitializeOption(UMCUpgradeBase* InUpgrade)
{
	Upgrade = InUpgrade;

	if (UpgradeNameText)
		UpgradeNameText->SetText(Upgrade->GetUpgradeName());

	if (DescriptionText)
		DescriptionText->SetText(Upgrade->GetUpgradeDescription());
}

bool UMCUpgradeOptionWidget::Initialize()
{
	if (!Super::Initialize()) return false;
	
	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &ThisClass::OnButtonClicked);
	}

	return true;
}

void UMCUpgradeOptionWidget::OnButtonClicked()
{
	OnUpgradeSelected.Broadcast(Upgrade);
}
