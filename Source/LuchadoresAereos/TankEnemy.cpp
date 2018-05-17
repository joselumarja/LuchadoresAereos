// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"


ATankEnemy::ATankEnemy() {
	Life = 100.0;
	Time = 20.0;
	Score = 50;
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



}

void ATankEnemy::Dodge()
{

}

void ATankEnemy::FindPlayer()
{

}