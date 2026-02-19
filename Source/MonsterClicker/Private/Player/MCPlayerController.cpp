// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterClicker/Public/Player/MCPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MCClickableInterface.h"
#include "MCClickableInterface.h"

class AMCPlayerState;
class UMCHealthComponent;



AMCPlayerController::AMCPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	DefaultMouseCursor = EMouseCursor::Hand;
}

void AMCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Input em UI + Game
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
}

void AMCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Adicionar Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputConfig && InputConfig->MappingContext)
		{
			Subsystem->AddMappingContext(InputConfig->GetMappingContext(), 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputConfig or MappingContext not set on %s"), *GetName());
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (InputConfig)
		{
			for (const auto& InputActionPair : InputConfig->InputActions)
			{
				const FGameplayTag& ActionTag = InputActionPair.Key;

				if (UInputAction* const* InputAction = &InputActionPair.Value)
				{
					if (ActionTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input.PrimaryClick"))))
					{
						EnhancedInput->BindAction(*InputAction, ETriggerEvent::Started, this, &ThisClass::HandlePrimaryClick);
					}
					// @TODO: Add New ones
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("InputConfig not set on %s"), *GetName());
		}
	}
}

void AMCPlayerController::HandlePrimaryClick()
{
	FHitResult Hit;
	if (!TraceUnderMouse(Hit))
		return;

	AActor* HitActor = Hit.GetActor();
	if (!HitActor)
		return;

	// Interface de clique
	if (HitActor->GetClass()->ImplementsInterface(UMCClickableInterface::StaticClass()))
	{
		IMCClickableInterface::Execute_OnClickedByPlayer(HitActor, ClickDamage);
	}
}

bool AMCPlayerController::TraceUnderMouse(FHitResult& OutHit) const
{
	float MouseX, MouseY;
	if (!GetMousePosition(MouseX, MouseY))
		return false;

	FVector WorldOrigin;
	FVector WorldDirection;

	if (!DeprojectScreenPositionToWorld(MouseX, MouseY, WorldOrigin, WorldDirection))
		return false;

	FVector End = WorldOrigin + WorldDirection * 100000.f;

	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(GetPawn()); // Mesmo sem pawn

	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		WorldOrigin,
		End,
		ECC_Visibility,
		Params
	);
}
