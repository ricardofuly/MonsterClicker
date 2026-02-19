// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCClickableInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MonsterClicker/Public/Combat/MCHealthComponent.h"
#include "MCEnemyBase.generated.h"

class UMCEnemyData;

UCLASS()
class MONSTERCLICKER_API AMCEnemyBase : public AActor, public IMCClickableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMCEnemyBase();
	
	void OnClickedByPlayer_Implementation(float Damage) override;
	
	UFUNCTION()
	void Die();
	
	void InitializeEnemy();
	
	void SetEnemyData(UMCEnemyData* NewData) { EnemyData = NewData; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UMCHealthComponent* HealthComp;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComp;
	
	UPROPERTY(VisibleAnywhere)
	UCharacterMovementComponent* CharacterMovementComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	UMCEnemyData* EnemyData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 XPReward = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DamagePerSecond = 1.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AttackRange = 150.f;
	
};
