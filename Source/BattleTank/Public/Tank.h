// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
//#include "Delegates/Delegate.h" 
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;



UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	FTankDelegate OnDeath;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable)
	void SetTurretReference(UTankTurret* TurretToSet);



	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// BlueprintPure erstellt uns eine Funktion die in Blueprints genutzt werden kann. Wir erhalten eine ReadOnly Function und können sicher sein, 
	// dass die Func nichts im Owner(hier Tank) verändert oder setted.
	// Get health in percent between 0 and 1
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

protected:
	UTankAimingComponent* TankAimingComponent = nullptr; 
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	
	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = Setup)
	int32 CurrentHealth;


};
