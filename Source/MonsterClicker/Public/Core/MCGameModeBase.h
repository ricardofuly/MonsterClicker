// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MonsterClicker/Public/Enemy/MCEnemyBase.h"
#include "MonsterClicker/Public/Enemy/MCEnemySpawner.h"
#include "MonsterClicker/Public/UI/MCLevelUpWidget.h"
#include "MonsterClicker/Public/Upgrade/MCUpgradeManager.h"
#include "MCGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EMCGameState : uint8
{
	WaitingToStart,
	Playing,
	LevelUP,
	GameOver
};

UCLASS()
class MONSTERCLICKER_API AMCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintCallable)
	void GameOver();
	
	UFUNCTION(BlueprintCallable)
	void SetGameState(EMCGameState NewState);
	
	UFUNCTION()
	void HandleLevelUp(int32 NewLevel);
	
	EMCGameState GetGameState() const { return MatchState; }

	
protected:
	virtual  void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	EMCGameState MatchState = EMCGameState::WaitingToStart;
	
	UPROPERTY(BlueprintReadOnly)
	float ElapsedTime = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Spawner")
	TSubclassOf<AMCEnemySpawner> EnemySpawnerClass;

	UPROPERTY()
	AMCEnemySpawner* EnemySpawner;
	
	UPROPERTY()
    UMCUpgradeManager* UpgradeManager;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMCLevelUpWidget> LevelUpWidgetClass;

	UPROPERTY()
	UMCLevelUpWidget* ActiveLevelUpWidget;
	
	void UpdateDifficulty();

	float DifficultyMultiplier = 1.f;
};
