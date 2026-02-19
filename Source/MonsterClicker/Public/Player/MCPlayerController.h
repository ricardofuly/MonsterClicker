// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Input/MCInputConfig.h"
#include "GameFramework/PlayerController.h"
#include "MCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MONSTERCLICKER_API AMCPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMCPlayerController();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void HandlePrimaryClick();
	
	bool TraceUnderMouse(FHitResult& OutHit) const;
	
	UPROPERTY(EditDefaultsOnly, Category="Click")
	float ClickDamage = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Click")
	UMCInputConfig* InputConfig;
};
