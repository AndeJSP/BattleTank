// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"



void UTankTurret::RotateTurret(float RelativeSpeed)
{

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//auto Elevation = FMath::Clamp(RawNewElevation, minElevationDegrees, maxElevationDegrees);
	//auto Elevation = FMath::Clamp<float>(RawNewElevation, minElevationDegrees, maxElevationDegrees);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("RelativeRotation %f"), Elevation)

}