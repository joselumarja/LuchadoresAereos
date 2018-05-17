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
		if (OtherActor->IsA(AStaticMeshActor::StaticClass())) {
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), Hit.Location);	
		}
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
		Destroy();
	}
	//DESACTIVADO HASTA IMPLEMENTAR EL ESQUIVAR
	//ChangeState(DodgeState);
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


/*void AEnemy::Move() {
	FVector NewLocation = GetActorLocation();
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FVector Distance = PlayerLocation - NewLocation;
	float DistanceSize = Distance.Size();
	//CAMBIAR EL CONTROL DE LA DISTANCIA AL TICK
	if (DistanceSize < 50.0f) {
		Shoot();
	}
	else {
		NewLocation.X -= 10.0f;
	}
	SetActorLocation(NewLocation);
}
*/
/*void AEnemy::Shoot() {
	// CAMBIAR A HIJOS
	// METER FIRE RATE
	FVector PlayerLocation = PlayerPawn->GetActorLocation() + GetActorForwardVector() * 250.0f;
	const FRotator FireRotation = PlayerLocation.Rotation();
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
	World->SpawnActor<ALuchadoresAereosProjectile>(SpawnLocation, FireRotation);
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
}*/