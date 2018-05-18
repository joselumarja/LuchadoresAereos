// Fill out your copyright notice in the Description page of Project Settings.

#include "TankEnemy.h"
#include "HeavyAmo.h"

ATankEnemy::ATankEnemy() :Super()
{
	Life = 100.0;
	Time = 20.0;
	Score = 50;
	FireRate = 3.0;
	MoveSpeed = 500.0;
	FIELD_OF_VIEW = 700.0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetStaticMesh(ShipMesh.Object);
}


void ATankEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ATankEnemy::Shot() {

	if (bCanFire)
	{
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, PlayerLocation.Z - EnemyLocation.Z).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<AHeavyAmo>(EnemyLocation, Rotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);
	}
	
	
}

void ATankEnemy::Dodge()
{
	float x;
	float y;
	float z = 215.0;

	x = FMath::RandRange(2000, 3000);
	y = FMath::RandRange(-1950, 1950);
	FVector RandomLocation(x, y, z);

	FVector EnemyLocation = GetActorLocation();
	FVector DirectionVector = RandomLocation - EnemyLocation;
	FVector NewLocation = (DirectionVector.GetSafeNormal()*(DeltaSeconds*MoveSpeed)) - EnemyLocation;
	SetActorLocation(NewLocation);

}

