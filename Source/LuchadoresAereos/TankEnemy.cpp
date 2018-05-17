// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"
#include "HeavyAmo.h"

ATankEnemy::ATankEnemy() :Super()
{
	Life = 100.0;
	Time = 20.0;
	Score = 50;
	FireRate = 3.0;
	MoveSpeed = 500.0;
	i = 0.0;

	FIELD_OF_VIEW = 700.0;

	GunOffset = FVector(90.f, 0.f, 0.f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void ATankEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	i++;
}

void ATankEnemy::Shot() {

	if (bCanFire)
	{
		if (i > (FireRate * 10.0)) {
			i = 0.0;
		/*	FVector PlayerLocation = PlayerPawn->GetActorLocation();
			FRotator FireRotation = GetActorRotation() - PlayerLocation.Rotation();
			FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);*/

			FVector PlayerLocation = PlayerPawn->GetActorLocation()+ GetActorForwardVector() * 250.0f;
			FRotator FireRotation = PlayerLocation.Rotation() ;
			FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
			World->SpawnActor<AHeavyAmo>(SpawnLocation, FireRotation);
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);
	bCanFire = true;
	
}

void ATankEnemy::Dodge()
{

}

