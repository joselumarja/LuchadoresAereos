// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"


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
		//PROPIEDADES DEL DISPARO
	}

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void ATankEnemy::Dodge()
{

}

