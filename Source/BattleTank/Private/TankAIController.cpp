// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

//////
/////
void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure (PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}

}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp,Warning, TEXT("Tank is Dead"))

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