#pragma once

#include "CoreMinimal.h"
#include "MCTypes.generated.h"


UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Normal      UMETA(DisplayName="Normal"),
	Fast        UMETA(DisplayName="Fast"),
	Tank        UMETA(DisplayName="Tank"),
	Elite       UMETA(DisplayName="Elite"),
	Boss        UMETA(DisplayName="Boss")
};
