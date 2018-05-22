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
	DodgeTime = 0.3f;
	FIELD_OF_VIEW = 700.0;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Enemigo1/StaticMesh.StaticMesh"));
	//ConstructorHelpers::FObjectFinder<UMaterialInstance> BaseMaterial(TEXT("/Game/TwinStick/Meshes/BlueMaterial.BlueMaterial"));

	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MediumMesh"));
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	MeshComponent->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	MeshComponent->SetupAttachment(RootComponent);
	RootComponent = MeshComponent;
	//MeshComponent->SetMaterial(0, BaseMaterial.Object);
	MeshComponent->BodyInstance.SetCollisionProfileName("MediumEnemy");
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetNotifyRigidBodyCollision(true);
	OnActorHit.AddDynamic(this, &AEnemy::OnHit);

}


void AMediumEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
}

void AMediumEnemy::Shot() {


	if (bCanFire)
	{
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<ABullet>(EnemyLocation, Rotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);

	}
	
}


