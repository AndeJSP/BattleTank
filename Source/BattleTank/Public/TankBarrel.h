// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public: 

	//-1 is the max downward speed and +1 the max up speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = 0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;
};
