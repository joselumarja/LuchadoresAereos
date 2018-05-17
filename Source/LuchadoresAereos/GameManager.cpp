// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Engine.h"

// Sets default values
AGameManager::AGameManager():Lives(3), Seconds(200), Round(0), EnemiesAlived(0), EnemiesKilledPerRound(0),
EnemiesKilled(0), Score(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	World = GetWorld();

	for (TActorIterator<AHUDManager>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("HUDManager_1")).Equals(ActorItr->GetName()))
		{
			//finding archievement manager
			HUD = *ActorItr;
		}
	}


	HUD->UpdateSeconds(Seconds);
	HUD->UpdateLives(Lives);
	HUD->UpdateScore(Score);
	InitializeSpawnEnemies();
	World->GetTimerManager().SetTimer(ClockTimer, this, &AGameManager::Clock, 1.0f);	
}


// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EnemiesAlived == EnemiesKilledPerRound) {
		EnemiesAlived = 0;
		EnemiesKilledPerRound = 0;
		Round++;
		SpawnEnemies(Round);
	}
	//SpawnEnemies(10);
}

void AGameManager::Clock()
{
	if (--Seconds == 0)
	{
		GameOver();
	}
	HUD->UpdateSeconds(Seconds);
	World->GetTimerManager().SetTimer(ClockTimer, this, &AGameManager::Clock, 1.0f);
}

void AGameManager::SumSeconds(uint8 ExtraSeconds)
{
	Seconds += ExtraSeconds;
}

void AGameManager::InitializeSpawnEnemies() {

	EnemyClasses.AddUnique(ALightEnemy::StaticClass());
	EnemyClasses.AddUnique(AMediumEnemy::StaticClass());
	EnemyClasses.AddUnique(ATankEnemy::StaticClass());
	
}

void AGameManager::UpdateLives()
{
	if (--Lives == 0)
	{
		GameOver();
	}
	HUD->UpdateLives(Lives);
}

void AGameManager::EnemyKilled(uint8 Score, uint8 ExtraTime)
{
	UpdateEnemyKilled();
	UpdateScore(Score);
	SumSeconds(ExtraTime);
}
void AGameManager::UpdateEnemyKilled() {

	EnemiesKilledPerRound++;
	HUD->UpdateEnemiesKilled(++EnemiesKilled);
}

void AGameManager::UpdateScore(uint8 ExtraScore) 
{
	Score += ExtraScore;
	HUD->UpdateScore(Score);
}

void AGameManager::SpawnEnemies(int Enemies) {

		for (int i = 0; i < Enemies; i++) 
		{
			TSubclassOf<AEnemy> EnemyType = GetRandomEnemyClass();
			FVector EnemySpawnLocation = GetRandomLocation();

			GetWorld()->SpawnActor(EnemyType, &EnemySpawnLocation);
			EnemiesAlived++;

		}
}

void AGameManager::GameOver()
{

}

TSubclassOf<AEnemy> AGameManager::GetRandomEnemyClass() const
{
	return EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
}

FVector AGameManager::GetRandomLocation() const
{
	
	/*//FVector Orgin;
	FVector BoundsExtent;
	ReferencePlane->GetActorBounds(false, Orgin, BoundsExtent);

	// Build a bounding box and get a random location.
	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Orgin, BoundsExtent));*/
	float x;
	float y;
	float z = 215.0;

	y = FMath::RandRange(-1950, 1950);
	x = FMath::RandRange(2900, 3000);
	FVector RandomLocation(x, y, z);
	return RandomLocation;
}
