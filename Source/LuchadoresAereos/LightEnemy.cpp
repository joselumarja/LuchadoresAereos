// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEnemy.h"
#include "LightBullet.h"

ALightEnemy::ALightEnemy() :Super()
{
	Life = 10.0;
	Time = 5.0;
	Score = 7;
	bCanFire = true;
	FireRate = 0.1;
	MoveSpeed = 1200.0;
	FIELD_OF_VIEW = 700.0;
	GunOffset = FVector(90.f, 0.f, 0.f);
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
		FRotator ShotRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
		FVector SpawnLocation = GetActorLocation() + GunOffset;
		World->SpawnActor<ALightBullet>(SpawnLocation, ShotRotation);
		//PROPIEDADES DEL DISPARO
	}

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void ALightEnemy::Dodge()
{

}


