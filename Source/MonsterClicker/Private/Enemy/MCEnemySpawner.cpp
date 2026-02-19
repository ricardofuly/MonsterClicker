// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Enemy/MCEnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "MonsterClicker/Public/Enemy/MCEnemyBase.h"
#include "MonsterClicker/Public/World/MCHouse.h"


// Sets default values
AMCEnemySpawner::AMCEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMCEnemySpawner::SetDifficultyMultiplier(float NewMultiplier)
{
	DifficultyMultiplier = NewMultiplier;

	float NewInterval = FMath::Clamp(BaseSpawnInterval / DifficultyMultiplier, 0.2f, BaseSpawnInterval);

	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AMCEnemySpawner::SpawnEnemy,
		NewInterval,
		true
	);
}

void AMCEnemySpawner::SpawnEnemy()
{
	if (!TargetHouse) return;

	int32 CurrentEnemies;
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass( GetWorld(),AMCEnemyBase::StaticClass(), Enemies);
	CurrentEnemies = Enemies.Num();

	if (CurrentEnemies >= MaxEnemiesAlive)
		return;

	TSubclassOf<AMCEnemyBase> EnemyClass;
	EnemyClass.GetDefaultObject()->SetEnemyData(ChooseEnemyClass()->GetDefaultObject<UMCEnemyData>());

	if (!EnemyClass) return;

	FVector SpawnLocation = GetRandomSpawnLocation();

	GetWorld()->SpawnActor<AMCEnemyBase>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
}

FVector AMCEnemySpawner::GetRandomSpawnLocation() const
{
	FVector HouseLocation = TargetHouse->GetActorLocation();

	FVector Direction = FMath::VRand();
	Direction.Z = 0.f;
	Direction.Normalize();

	FVector SpawnLocation = HouseLocation + Direction * SpawnRadius;

	return SpawnLocation;
}

TSubclassOf<UMCEnemyData> AMCEnemySpawner::ChooseEnemyClass() const
{
	TArray<FEnemySpawnData> Available;

	for (const FEnemySpawnData& Data : EnemyTypes)
	{
		if (DifficultyMultiplier >= Data.MinDifficulty)
		{
			Available.Add(Data);
		}
	}

	if (Available.Num() == 0)
		return nullptr;

	float TotalWeight = 0.f;
	for (const auto& Data : Available)
	{
		TotalWeight += Data.Weight;
	}

	float RandomValue = FMath::FRandRange(0.f, TotalWeight);

	float RunningSum = 0.f;
	for (const auto& Data : Available)
	{
		RunningSum += Data.Weight;
		if (RandomValue <= RunningSum)
		{
			return Data.EnemyClass;
		}
	}

	return Available.Last().EnemyClass;
}

// Called when the game starts or when spawned
void AMCEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	TargetHouse = Cast<AMCHouse>(
		UGameplayStatics::GetActorOfClass(GetWorld(), AMCHouse::StaticClass())
	);

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AMCEnemySpawner::SpawnEnemy,
		BaseSpawnInterval,
		true
	);
	
}

