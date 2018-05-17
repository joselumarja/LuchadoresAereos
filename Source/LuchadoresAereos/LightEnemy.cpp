// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEnemy.h"


ALightEnemy::ALightEnemy() :Super()
{
	Life = 10.0;
	Time = 5.0;
	Score = 7;
	bCanFire = true;
	FireRate = 0.1;
	MoveSpeed = 1200.0;
	FIELD_OF_VIEW = 700.0;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void ALightEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ALightEnemy::Shot() {
	if (bCanFire)
	{
		//PROPIEDADES DEL DISPARO
	}

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void ALightEnemy::Dodge()
{

}


