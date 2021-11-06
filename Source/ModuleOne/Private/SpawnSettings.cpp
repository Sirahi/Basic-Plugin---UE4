#include "SpawnSettings.h"

USpawnSettings::USpawnSettings(const FObjectInitializer& ObjectInitializer)
	: xValue(0.0), yValue(0.0), zValue(0.0)
{

}

FVector USpawnSettings::GetCoordinates()
{
	return FVector(xValue, yValue, zValue);
}