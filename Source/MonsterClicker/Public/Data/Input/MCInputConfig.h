// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MCInputConfig.generated.h"


class UInputMappingContext;
class UInputAction;

UCLASS(Blueprintable)
class MONSTERCLICKER_API UMCInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UInputMappingContext* GetMappingContext() const { return MappingContext; }
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* MappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, UInputAction*> InputActions;
};
