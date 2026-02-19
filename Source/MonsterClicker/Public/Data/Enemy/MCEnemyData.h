// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MCEnemyData.generated.h"

enum class EEnemyType : uint8;
/**
 * 
 */
UCLASS()
class MONSTERCLICKER_API UMCEnemyData : public UDataAsset
{
	GENERATED_BODY()
public:

	// Identity
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	FName EnemyID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Enemy")
	EEnemyType EnemyType;

	// Attributes
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	float MaxHealth = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	float MoveSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	float DamagePerSecond = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	float AttackRange = 150.f;

	// Progression
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Progression")
	int32 XPReward = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Progression")
	int32 Weight = 1; // Chance to Spawn

	// Visual
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visual")
	USkeletalMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visual")
	UMaterialInterface* Material;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visual")
	FVector MeshScale = FVector(1.f);

	// Feedback
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FX")
	UParticleSystem* HitFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FX")
	USoundBase* DeathSound;
};
