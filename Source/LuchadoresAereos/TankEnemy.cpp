// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"
#include "TankBullet.h"

ATankEnemy::ATankEnemy() :Super()
{
	Life = 100.0;
	Time = 20.0;
	Score = 50;
	bCanFire = true;
	FireRate = 1.5;
	MoveSpeed = 300.0;
	FIELD_OF_VIEW = 6000.0;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void ATankEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

}

void ATankEnemy::Shot() {

	if (bCanFire)
	{
		// DISPAROS POR CUADRAR

		FVector PlayerLocation = PlayerPawn->GetActorLocation() + GetActorForwardVector() * 250.0f;
		const FRotator FireRotation = PlayerLocation.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		World->SpawnActor<ATankBullet>(SpawnLocation, FireRotation);

		FVector SpawnLocation2 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FRotator SpawnRotation2 = GetActorRotation().Add(0.0f, 15.0f, 0.0f);
		World->SpawnActor<ATankBullet>(SpawnLocation2, SpawnRotation2);

		FVector SpawnLocation3 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FRotator SpawnRotation3 = GetActorRotation().Add(0.0f, 30.0f, 0.0f);
		World->SpawnActor<ATankBullet>(SpawnLocation3, SpawnRotation3);

		FVector SpawnLocation4 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FRotator SpawnRotation4 = GetActorRotation().Add(0.0f, 30.0f, 0.0f);
		World->SpawnActor<ATankBullet>(SpawnLocation4, SpawnRotation4);

		FVector SpawnLocation5 = GetActorLocation() + GetActorForwardVector() * 500.0f;
		FRotator SpawnRotation5 = GetActorRotation().Add(0.0f, 30.0f, 0.0f);
		World->SpawnActor<ATankBullet>(SpawnLocation5, SpawnRotation5);

		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void ATankEnemy::Dodge()
{

}

void ATankEnemy::FindPlayer()
{

}