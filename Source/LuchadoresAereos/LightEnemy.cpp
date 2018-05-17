// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEnemy.h"




ALightEnemy::ALightEnemy() {
	Life = 10.0;
	Time = 5.0;
	Score = 7;
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



}

void ALightEnemy::Dodge()
{

}

void ALightEnemy::FindPlayer()
{

}

