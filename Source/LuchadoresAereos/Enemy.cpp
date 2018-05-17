// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "GameManager.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	FRotator NewRotation(0.0f, 180.0f, 0.0f);
	SetActorRotation(NewRotation);
	World = GetWorld();
	

	for (TActorIterator<AGameManager>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("GameManager_1")).Equals(ActorItr->GetName()))
		{
			//finding manager
			Manager = *ActorItr;
		}
	}
	
}
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	RotateToPlayer();
}

void AEnemy::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor) {
		if (OtherActor->IsA(AStaticMeshActor::StaticClass())) {
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);	
		}
	}
}

void AEnemy::UpdateLife(uint8 Damage)
{
	Life -= Damage;

	if (Life <= 0)
	{
		Manager->EnemyKilled(Score,Time);
		Destroy();
	}
}

void AEnemy::Move() {
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= 2.0f;
	SetActorLocation(NewLocation);
}

void AEnemy::RotateToPlayer() {
/*
	FRotator EnemyRotation = FRotationMatrix::MakeFromX(PlayerPawn->GetActorLocation() - GetActorLocation()).Rotator();
	MeshComponent->SetRelativeRotation(EnemyRotation, false, nullptr, ETeleportType::TeleportPhysics);
*/
}