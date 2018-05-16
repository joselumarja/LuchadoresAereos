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
	FRotator NewRotation(0.0f, 180.0f, 0.0f);
	SetActorRotation(NewRotation);
	World = GetWorld();
	
	//OBTENER PLAYERPAWN PARA PODER IR ROTANDO HACIA EL PLAYER

	/*for (TActorIterator<ALuchadoresAereosPawn>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("TP_TwinStickPawn")).Equals(ActorItr->GetName()))
		{
			//finding archievement manager
			PlayerPawn = *ActorItr;
		}
	}*/
	
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
		/*Manager->UpdateEnemyKilled;
		Manager->UpdateScore(Score);
		Manager->SumSeconds(Time);*/

		//INCLUIR OBSERVER PARA NOTIFICAR AQUI
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