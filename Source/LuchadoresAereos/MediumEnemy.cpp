// Fill out your copyright notice in the Description page of Project Settings.

#include "MediumEnemy.h"
#include "Bullet.h"


AMediumEnemy::AMediumEnemy() :Super()
{
	Life = 50.0;
	Time = 12.0;
	Score = 15;
	FireRate = 0.5;
	MoveSpeed = 800.0;
	FIELD_OF_VIEW = 700.0;
	GunOffset = FVector(90.f, 0.f, 0.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MediumMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	MeshComponent->SetNotifyRigidBodyCollision(true);

}


void AMediumEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	i++;
}

void AMediumEnemy::Shot() {

	if (i > (FireRate * 10.0)) {
		i = 0.0;

		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FRotator FireRotation = PlayerLocation.Rotation();
		FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		World->SpawnActor<ABullet>(SpawnLocation, FireRotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

}

void AMediumEnemy::Dodge()
{


}


