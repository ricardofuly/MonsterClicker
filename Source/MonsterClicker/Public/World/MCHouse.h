// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MonsterClicker/Public/Combat/MCHealthComponent.h"
#include "MCHouse.generated.h"

UCLASS()
class MONSTERCLICKER_API AMCHouse : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMCHouse();
	
	UFUNCTION()
	void OnHouseDestroyed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UMCHealthComponent* HealthComp;
	
	UPROPERTY(VisibleAnywhere, Category="House")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category="House")
	UBoxComponent* DamageArea;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	
	float CurrentHealth = MaxHealth;
};
