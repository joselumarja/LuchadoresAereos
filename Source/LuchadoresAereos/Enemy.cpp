// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

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

	World = GetWorld();
}
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AEnemy::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor) {
		//SelfActor->SetActorEnableCollision(false);
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
		//INCLUIR OBSERVER PARA NOTIFICAR AQUI
		Destroy();
	}
}

void AEnemy::Move() {
	FVector NewLocation = GetActorLocation();
	NewLocation.X -= 2.0f;
	SetActorLocation(NewLocation);


}