// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"




void UTankTracks::SetThrottle(float Throttle)
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT(" %s Throttle: %f"), *Name, Throttle)

	auto ForceApplied = GetForwardVector() *  Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}

/*
void UTankTracks::OnHit(UPrimitiveComponent* HitComponent,)
{


}
*/


