// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// #include "Runtime/Core/Public/Math/Vector2D.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else {

		// log
	}


	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT(" %s"), *(GetControlledTank()->GetName()))
		
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT(" no tank possessed") )
	}

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("working?"))

	//auto TankForward = GetPawn()->GetRootComponent()->GetOwner()->GetActorForwardVector().GetSafeNormal();
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *TankForward.ToString())
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	{
		FVector HitLocation;
		//GetWorld()->
		if (GetSightRayHitLocation(HitLocation))
		{
			GetControlledTank()->AimAt(HitLocation);
			//UE_LOG(LogTemp, Warning, TEXT("%s"),*HitLocation.ToString() )
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	//OutHitLocation = FVector(1.0);		//PlayerLocation + PlayerRotation.Vector() * 20000.0;

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = {ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation};
	// auto ScreenLocation = FVector2D( ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetVectorHitLookLocation( LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{

	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

}

bool ATankPlayerController::GetVectorHitLookLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = { 0,0,0 };
	return false;
		
}

/*
void ATankPlayerController::FoundAimingComponent(UTankAimingComponent* AimingCompRef)
{



}
*/