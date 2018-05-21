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
	bCanDodge = false;
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
			//finding pawn
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

void AEnemy::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ALuchadoresAereosProjectile::StaticClass())||OtherActor->IsA(AEnemy::StaticClass())) {
		DodgeDirection = (GetActorLocation() - OtherActor->GetActorLocation());
		DodgeDirection.Z = 0.f;
		ChangeState(DodgeState);
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
		Manager->DropPowerUp(GetActorLocation());
		Destroy();
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
	MoveTo(DirectionVector, ActualLocation, MoveSpeed);
}

void AEnemy::MoveTo(FVector DirectionVector,FVector ActualLocation,float Velocity)
{
	FVector Movement = (DirectionVector.GetSafeNormal()*(DeltaSeconds*Velocity)) ;
	const FRotator NewRotation(0, 0, 0);
	FHitResult Hit(1.f);
	RootComponent->MoveComponent(Movement, NewRotation, true);

	if (Hit.IsValidBlockingHit())
	{
		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		RootComponent->MoveComponent(Deflection, NewRotation, true);
	}
}

void AEnemy::DodgeFinish()
{
	bCanDodge = false;
}

void AEnemy::SetTimerDodge()
{
	World->GetTimerManager().SetTimer(TimerHandle_DodgeFinish, this, &AEnemy::DodgeFinish, DodgeTime);
}

void AEnemy::Dodge()
{
	MoveTo(DodgeDirection, GetActorLocation(), MoveSpeed * 2);
}
