// Fill out your copyright notice in the Description page of Project Settings.

#include "MediumEnemy.h"
#include "Bullet.h"


AMediumEnemy::AMediumEnemy() :Super()
{
	Life = 50.0;
	Time = 12.0;
	Score = 15;
	bCanFire = true;
	FireRate = 0.5;
	MoveSpeed = 600.0;
	FIELD_OF_VIEW = 4000.0;
	GunOffset = FVector(90.f, 0.f, 0.f);

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

	if (bCanFire)
	{
		FVector PlayerLocation = PlayerPawn->GetActorLocation() + GetActorForwardVector() * 250.0f;
		FRotator FireRotation = PlayerLocation.Rotation();
		FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		World->SpawnActor<ABullet>(SpawnLocation, FireRotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void AMediumEnemy::Dodge()
{

}


