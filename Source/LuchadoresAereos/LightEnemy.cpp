// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEnemy.h"
#include "LightBullet.h"

ALightEnemy::ALightEnemy() :Super()
{
	Life = 10.0;
	Time = 5.0;
	Score = 7;
	FireRate = 0.1;
	MoveSpeed = 1200.0;
	FIELD_OF_VIEW = 500.0;
	GunOffset = FVector(90.f, 0.f, 0.f);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	RootComponent = MeshComponent;
	MeshComponent->OnComponentHit.AddDynamic(this, &ALuchadoresAereosProjectile::OnHit);
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void ALightEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ALightEnemy::Shot() {

	FVector ActualLocation = GetActorLocation();
	FVector DirectionVector = PlayerPawn->GetActorLocation() - ActualLocation;
	FVector NewLocation = (DirectionVector.GetSafeNormal()*(DeltaSeconds*MoveSpeed)) + ActualLocation;
	SetActorLocation(NewLocation);
	
}

void ALightEnemy::Dodge()
{


}


