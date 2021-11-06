#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "SpawnSettings.generated.h"

UCLASS(Config = Editor)
class USpawnSettings : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(Config, DisplayName = "X", EditAnywhere, Category = "SpawnSettings")
		float xValue;
	UPROPERTY(Config, DisplayName = "Y", EditAnywhere, Category = "SpawnSettings")
		float yValue;
	UPROPERTY(Config, DisplayName = "Z", EditAnywhere, Category = "SpawnSettings")
		float zValue;

	FVector GetCoordinates();
};