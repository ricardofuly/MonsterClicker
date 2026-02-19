// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Enemy/MCEnemyBase.h"

#include "Data/Enemy/MCEnemyData.h"
#include "Kismet/GameplayStatics.h"
#include "MonsterClicker/Public/Player/MCPlayerState.h"


// Sets default values
AMCEnemyBase::AMCEnemyBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	HealthComp = CreateDefaultSubobject<UMCHealthComponent>(FName("HealthComp"));
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(GetRootComponent());
	
	CharacterMovementComp = CreateDefaultSubobject<UCharacterMovementComponent>(FName("CharacterMovementComp"));
}

void AMCEnemyBase::OnClickedByPlayer_Implementation(float Damage)
{
	HealthComp->ApplyDamage(Damage);
}

void AMCEnemyBase::Die()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (APlayerState* PS = PC->GetPlayerState<APlayerState>())
		{
			if (AMCPlayerState* ClickerPS = Cast<AMCPlayerState>(PS))
			{
				ClickerPS->AddXP(XPReward);
			}
		}
	}
	
	if (EnemyData && EnemyData->DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			EnemyData->DeathSound,
			GetActorLocation()
		);
	}

	Destroy();
}

void AMCEnemyBase::InitializeEnemy()
{
	if (!EnemyData) return;

	HealthComp->SetMaxHealth(EnemyData->MaxHealth);

	CharacterMovementComp->MaxWalkSpeed = EnemyData->MoveSpeed;
	DamagePerSecond = EnemyData->DamagePerSecond;
	AttackRange = EnemyData->AttackRange;
	XPReward = EnemyData->XPReward;

	if (EnemyData->Mesh)
		SkeletalMeshComp->SetSkeletalMesh(EnemyData->Mesh);

	if (EnemyData->Material)
		SkeletalMeshComp->SetMaterial(0, EnemyData->Material);

	SkeletalMeshComp->SetWorldScale3D(EnemyData->MeshScale);
}

// Called when the game starts or when spawned
void AMCEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComp->OnDeath.AddDynamic(this, &ThisClass::Die);	
}


