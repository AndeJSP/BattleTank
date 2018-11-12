// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"




// Elevate the Barrel with a Relative Clamped Speed
void UTankBarrel::Elevate(float RelativeSpeed) 
{
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp(RawNewElevation, minElevationDegrees, maxElevationDegrees);
	//auto Elevation = FMath::Clamp<float>(RawNewElevation, minElevationDegrees, maxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation,0,0));
	//UE_LOG(LogTemp, Warning, TEXT("RelativeRotation %f"), Elevation)
}

