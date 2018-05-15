// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "EngineMinimal.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*auto FirstPersonProjectileBPClass = ConstructorHelpers::FClassFinder<AActor>(TEXT("Class'/Script/LuchadoresAereos.LuchadoresAereosProjectile'"));
	if (FirstPersonProjectileBPClass.Succeeded()) {
		ProjectileClass = FirstPersonProjectileBPClass.Class;
	}

	OnActorHit.AddDynamic(this, &AEnemy::OnHit);*/
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AGameManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("GameManager_1")).Equals(ActorItr->GetName()))
		{
			//finding archievement manager
			//Manager = *ActorItr;
		}
	}
	World = GetWorld();
}
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor) {

		if (OtherActor->IsA(ProjectileClass)) {
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);
			
		}

		
	}
}

void AEnemy::UpdateLife(uint8 Damage)
{
	Life -= Damage;

	if (Life <= 0)
	{
		/*Manager->SumSeconds(Time);
		Manager->UpdateScore(Score);
		Manager->UpdateEnemyKilled();*/
		Destroy();
	}
}


