// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledPawn = Cast<ATank>(GetPawn());
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, AcceptanceRadius);

		ControlledPawn->AimAt(PlayerPawn->GetActorLocation());
		ControlledPawn->Fire();
	}

}