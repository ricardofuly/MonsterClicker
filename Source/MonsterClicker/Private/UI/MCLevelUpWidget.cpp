// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/UI/MCLevelUpWidget.h"

#include "Components/HorizontalBox.h"
#include "MonsterClicker/Public/Core/MCGameModeBase.h"
#include "MonsterClicker/Public/UI/MCUpgradeOptionWidget.h"

void UMCLevelUpWidget::InitializeLevelUp(const TArray<UMCUpgradeBase*>& UpgradeChoices)
{
	if (!OptionsContainer || !OptionWidgetClass)
		return;

	OptionsContainer->ClearChildren();

	for (UMCUpgradeBase* Upgrade : UpgradeChoices)
	{
		UMCUpgradeOptionWidget* OptionWidget =
			CreateWidget<UMCUpgradeOptionWidget>(this, OptionWidgetClass);

		OptionWidget->InitializeOption(Upgrade);
		OptionWidget->OnUpgradeSelected.AddDynamic(this, &ThisClass::HandleUpgradeSelected);

		OptionsContainer->AddChild(OptionWidget);
	}
}

void UMCLevelUpWidget::HandleUpgradeSelected(UMCUpgradeBase* SelectedUpgrade)
{
	if (!SelectedUpgrade)
		return;

	APlayerController* PC = GetOwningPlayer();
	if (!PC)
		return;

	AMCPlayerState* PS = PC->GetPlayerState<AMCPlayerState>();
	if (PS)
	{
		PS->AddUpgrade(SelectedUpgrade);
	}

	if (AMCGameModeBase* GM = GetWorld()->GetAuthGameMode<AMCGameModeBase>())
	{
		GM->SetGameState(EMCGameState::Playing);
	}

	RemoveFromParent();
}
