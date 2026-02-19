// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/World/MCHouse.h"

#include "MonsterClicker/Public/Core/MCGameModeBase.h"


// Sets default values
AMCHouse::AMCHouse()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	
	HealthComp = CreateDefaultSubobject<UMCHealthComponent>(TEXT("HealthComp"));
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("BlockAll");
	
	DamageArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageArea"));
	DamageArea->SetupAttachment(RootComponent);
	DamageArea->SetCollisionProfileName("OverlapAll");
}

void AMCHouse::OnHouseDestroyed()
{
	if (AMCGameModeBase* GM = GetWorld()->GetAuthGameMode<AMCGameModeBase>())
	{
		GM->GameOver();
	}
}

// Called when the game starts or when spawned
void AMCHouse::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComp)
	{
		HealthComp->OnDeath.AddDynamic(this, &ThisClass::OnHouseDestroyed);
	}	
}


