// Fill out your copyright notice in the Description page of Project Settings.

#include "LightEnemy.h"
#include "LightBullet.h"

ALightEnemy::ALightEnemy() :Super(),RafagaNumber(0)
{
	Life = 10.0;
	Time = 5.0;
	Score = 7;
	FireRate = 0.2;
	MoveSpeed = 1000.0;
	FIELD_OF_VIEW = 500.0;
	DodgeTime = 0.02f;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Testeo/SM_MERGED_unibike_sharky_tire_8.SM_MERGED_unibike_sharky_tire_8"));

	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightMesh"));
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	MeshComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	MeshComponent->SetWorldRotation(FRotator(0.f, 90.f, 0.f));
	MeshComponent->SetupAttachment(RootComponent);
	RootComponent = MeshComponent;
	MeshComponent->BodyInstance.SetCollisionProfileName("LightEnemy");
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetNotifyRigidBodyCollision(true);
	OnActorHit.AddDynamic(this, &AEnemy::OnHit);

}


void ALightEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ALightEnemy::Shot() {
	if (bCanFire)
	{
		FVector EnemyLocation = GetActorLocation();
		FVector PlayerLocation = PlayerPawn->GetActorLocation();
		FVector DirectionVector = FVector(PlayerLocation.X - EnemyLocation.X, PlayerLocation.Y - EnemyLocation.Y, .0f).GetSafeNormal();
		FRotator Rotation = DirectionVector.Rotation();
		EnemyLocation = EnemyLocation + (DirectionVector * 100);
		World->SpawnActor<ALightBullet>(EnemyLocation, Rotation);
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

		bCanFire = false;
		if (RafagaNumber < 3)
		{
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, FireRate);
			RafagaNumber++;
		}
		else
		{
			RafagaNumber = 0;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemy::ShotTimerExpired, 0.4f);
		}
		
	}
	
	
}



