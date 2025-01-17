// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelRefrence(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts

void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	//Calculate the OUTLaunch Velocity	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// workout a difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator:%s"), *AimAsRotator.ToString());
	//move the barrel right amount this frame

	//given a max elevation speed,and this frame time
}