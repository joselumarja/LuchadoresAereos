// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"


ATankEnemy::ATankEnemy() {
	Life = 100.0;
	Time = 20.0;
	
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

void ATankEnemy::UpdateState() {
	//PENSADO PARA CAMBIAR DE FASE

}

void ATankEnemy::Move() {

	FVector NewLocation = GetActorLocation();
	NewLocation.X -= 5.0f;
	SetActorLocation(NewLocation);

}