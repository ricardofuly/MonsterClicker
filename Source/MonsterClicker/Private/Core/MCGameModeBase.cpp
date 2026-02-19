// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Core/MCGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "MonsterClicker/Public/Player/MCPlayerState.h"

void AMCGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (MatchState != EMCGameState::Playing)
		return;

	ElapsedTime += DeltaSeconds;

	UpdateDifficulty();
}

void AMCGameModeBase::StartGame()
{
	SetGameState(EMCGameState::Playing);

	if (EnemySpawnerClass)
	{
		EnemySpawner = GetWorld()->SpawnActor<AMCEnemySpawner>(EnemySpawnerClass);
	}
}

void AMCGameModeBase::GameOver()
{
	SetGameState(EMCGameState::GameOver);
}

void AMCGameModeBase::SetGameState(EMCGameState NewState)
{
	MatchState = NewState;

	switch (MatchState)
	{
	case EMCGameState::Playing:
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		break;

	case EMCGameState::LevelUP:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;

	case EMCGameState::GameOver:
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		break;

	default:
		break;
	}
}

void AMCGameModeBase::HandleLevelUp(int32 NewLevel)
{
	SetGameState(EMCGameState::LevelUP);
	
	if (!LevelUpWidgetClass || !UpgradeManager) return;
	
	TArray<UMCUpgradeBase*> Choices = UpgradeManager->GetUpgradeChoices(3);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	ActiveLevelUpWidget = CreateWidget<UMCLevelUpWidget>(PC, LevelUpWidgetClass);

	// @TODO: Use UI Manager Calls
	ActiveLevelUpWidget->AddToViewport();
	ActiveLevelUpWidget->InitializeLevelUp(Choices);		
}

void AMCGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	StartGame();
	
	AMCPlayerState* PS = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMCPlayerState>();

	// Bind to level up event
	if (PS)
	{
		PS->OnLevelUp.AddDynamic(this, &AMCGameModeBase::HandleLevelUp);
	}
	
	// Initialize Upgrade Manager
	UpgradeManager = NewObject<UMCUpgradeManager>(this);
	UpgradeManager->Initialize(PS);
}

void AMCGameModeBase::UpdateDifficulty()
{
	DifficultyMultiplier = 1.f + (ElapsedTime / 30.f);

	if (EnemySpawner)
	{
		EnemySpawner->SetDifficultyMultiplier(DifficultyMultiplier);
	}
}
