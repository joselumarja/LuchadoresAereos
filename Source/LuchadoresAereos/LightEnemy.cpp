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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetStaticMesh(ShipMesh.Object);

}


void ALightEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ALightEnemy::Shot() {

	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, PlayerLocation.Z - EnemyLocation.Z).GetSafeNormal();
	FRotator Rotation = DirectionVector.Rotation();
	EnemyLocation = EnemyLocation + (DirectionVector * 100);
	World->SpawnActor<ALightBullet>(EnemyLocation, Rotation);
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);
	
}

void ALightEnemy::Dodge()
{


}


