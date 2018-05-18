// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "GameManager.h"
#include "LuchadoresAereosProjectile.h"
#include "EnemyState.h"
#include "DodgeState.h"
#include "FindPlayerState.h"
#include "ShotState.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;
	bCanFire = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	FRotator NewRotation(0.0f, 180.0f, 0.0f);
	SetActorRotation(NewRotation);
	World = GetWorld();
	
	for (TActorIterator<ALuchadoresAereosPawn>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("TP_TwinStickPawn_1")).Equals(ActorItr->GetName()))
		{
			//finding manager
			PlayerPawn = *ActorItr;
		}
	}
	
	for (TActorIterator<AGameManager>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("GameManager_1")).Equals(ActorItr->GetName()))
		{
			//finding manager
			Manager = *ActorItr;
		}
	}
	
	DodgeState = NewObject<UDodgeState>();
	FindPlayerState = NewObject<UFindPlayerState>();
	ShotState = NewObject<UShotState>();

	ChangeState(FindPlayerState);

}
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaSeconds = DeltaTime;
	CurrentState->Update(*this);
}

float AEnemy::DistanceToPlayer()
{
	FVector PlayerPoint = PlayerPawn->GetActorLocation();
	FVector EnemyPoint = GetActorLocation();
	float x, y, z;
	x = PlayerPoint.X - EnemyPoint.X;
	x = x * x;
	y = PlayerPoint.Y - EnemyPoint.Y;
	y = y * y;
	z = PlayerPoint.Z - EnemyPoint.Z;
	z = z * z;

	return FMath::Sqrt(x + y + z);
}

void AEnemy::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor) {
		
	}
}

void AEnemy::ShotTimerExpired()
{
	bCanFire = true;
}

void AEnemy::UpdateLife(uint8 Damage)
{
	Life -= Damage;

	if (Life <= 0)
	{
		Manager->EnemyKilled(Score,Time);
		DropPowerUp();
		Destroy();
	}
	else if (Life < 45.0) {
		ChangeState(DodgeState);
	}
}

void AEnemy::ChangeState(const TScriptInterface<IEnemyState>& State)
{
	if (!CurrentState) {
		CurrentState = Cast<IEnemyState>(FindPlayerState);
	}

	OldState = CurrentState;
	CurrentState = (IEnemyState*)State.GetInterface();
	CurrentState->Enter(*OldState, *this);
}


void AEnemy::FindPlayer()
{
	FVector ActualLocation = GetActorLocation();
	FVector DirectionVector = PlayerPawn->GetActorLocation() - ActualLocation;
	FVector NewLocation = (DirectionVector.GetSafeNormal()*(DeltaSeconds*MoveSpeed)) + ActualLocation;
	SetActorLocation(NewLocation);
}


void AEnemy::DropPowerUp() {
	if (CalculateDropProbability()) {


	}
}

bool AEnemy::CalculateDropProbability() {
	return (FMath::RandRange(1, 100 / 10) == 1 ? true : false);
}