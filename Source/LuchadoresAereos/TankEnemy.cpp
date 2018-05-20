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
	DodgeTime = 0.5f;
	FIELD_OF_VIEW = 700.0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Enemigo_Pesado/UFO_2"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankMesh"));
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	RootComponent = MeshComponent;
	MeshComponent->BodyInstance.SetCollisionProfileName("TankEnemy");
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetNotifyRigidBodyCollision(true);
	OnActorHit.AddDynamic(this, &AEnemy::OnHit);
}


void ATankEnemy::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
}

void ATankEnemy::Shot() {

	if (bCanFire)
	{
		FVector EnemyLocation = GetActorLocation();
		FVector EnemyFordwardVector = GetActorForwardVector();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();

		EnemyLocation = EnemyLocation + (DirectionVector * 300);
		FVector EnemyLocation1, EnemyLocation2, EnemyLocation3;
		EnemyLocation1 = EnemyLocation;
		EnemyLocation2 = EnemyLocation + EnemyFordwardVector * 100;
		EnemyLocation3 = EnemyLocation - EnemyFordwardVector * 100;

		World->SpawnActor<AHeavyAmo>(EnemyLocation1, Rotation);
		World->SpawnActor<AHeavyAmo>(EnemyLocation2, Rotation);
		World->SpawnActor<AHeavyAmo>(EnemyLocation3, Rotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);
	}
	
	
}


