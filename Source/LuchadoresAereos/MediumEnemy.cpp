// Fill out your copyright notice in the Description page of Project Settings.

#include "MediumEnemy.h"



AMediumEnemy::AMediumEnemy() {
	Life = 50.0;
	Time = 12.0;
	Score = 15;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MediumMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void AMediumEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AMediumEnemy::Shot() {



}

void AMediumEnemy::Dodge()
{

}

void AMediumEnemy::FindPlayer()
{

}
