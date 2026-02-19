// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Enemy/MCEnemyData.h"
#include "GameFramework/Actor.h"
#include "MCEnemySpawner.generated.h"

class AMCHouse;
class AMCEnemyBase;

USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMCEnemyData> EnemyClass;

	UPROPERTY(EditAnywhere)
	float Weight = 1.f;

	UPROPERTY(EditAnywhere)
	float MinDifficulty = 1.f;
};

UCLASS()
class MONSTERCLICKER_API AMCEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMCEnemySpawner();
	
	void SetDifficultyMultiplier(float NewMultiplier);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Settings
	UPROPERTY(EditDefaultsOnly, Category="Spawn")
	float SpawnRadius = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category="Spawn")
	float BaseSpawnInterval = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="Spawn")
	int32 MaxEnemiesAlive = 100;

	UPROPERTY(EditDefaultsOnly, Category="Spawn")
	TArray<FEnemySpawnData> EnemyTypes;
	
	UPROPERTY()
	AMCHouse* TargetHouse;

	float DifficultyMultiplier = 1.f;

	FTimerHandle SpawnTimerHandle;

	void SpawnEnemy();
	FVector GetRandomSpawnLocation() const;
	TSubclassOf<UMCEnemyData> ChooseEnemyClass() const;
};
