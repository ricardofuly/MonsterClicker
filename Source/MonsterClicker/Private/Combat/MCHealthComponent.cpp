// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Combat/MCHealthComponent.h"


// Sets default values for this component's properties
UMCHealthComponent::UMCHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMCHealthComponent::ApplyDamage(float DamageAmount)
{
	if (DamageAmount <= 0.f || IsDead())
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0.f)
	{
		OnDeath.Broadcast();
	}
}

void UMCHealthComponent::Heal(float Amount)
{
	if (Amount <= 0.f || IsDead())
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth);
}


// Called when the game starts
void UMCHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


