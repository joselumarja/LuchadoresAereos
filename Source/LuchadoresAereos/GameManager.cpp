// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "MySaveGame.h"
#include "LuchadoresAereosPawn.h"
#include "Engine.h"

// Sets default values
AGameManager::AGameManager():Lives(3), Seconds(200), Round(0), EnemiesAlived(0), EnemiesKilledPerRound(0),
EnemiesKilled(0), Score(0), DropRatio(25)
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
			break;
		}
	}

	for (TActorIterator<AActor>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("SpawnPlane")).Equals(ActorItr->GetName()))
		{
			//finding archievement manager
			ReferencePlane = *ActorItr;
			break;
		}
	}

	for (TActorIterator<ALuchadoresAereosPawn>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("TP_TwinStickPawn_1")).Equals(ActorItr->GetName()))
		{
			//finding manager
			PlayerPawn = *ActorItr;
			break;
		}
	}


	HUD->UpdateSeconds(Seconds);
	HUD->UpdateLives(Lives);
	HUD->UpdateScore(Score);
	InitializeSpawnEnemies();
	InitializePerks();
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

// Called to add the extra seconds from enemies killed 
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

	FVector PreviousSpawn = FVector(0, 0, 0);
	for (int i = 0; i < Enemies; i++) {
		TSubclassOf<AEnemy> EnemyType = GetRandomEnemyClass();
		FVector EnemySpawnLocation = GetRandomLocation(PreviousSpawn);

		GetWorld()->SpawnActor(EnemyType, &EnemySpawnLocation);
		PreviousSpawn = EnemySpawnLocation;
		EnemiesAlived++;
	}

}

// Called when finish the game, saves the score and the enemies killed
void AGameManager::GameOver()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	UMySaveGame* CheckSaveGameInstance=Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
	if (CheckSaveGameInstance != NULL)
	{
		SaveGameInstance = CheckSaveGameInstance;
	}
	FText Name = FText::FromString(FDateTime::Now().ToString());
	SaveGameInstance->UpdateRecords((int32)EnemiesKilled, Name, (int32)Score);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/TwinStickCPP/Maps/GameOverMap.GameOverMap"), TRAVEL_Absolute);
}

TSubclassOf<AEnemy> AGameManager::GetRandomEnemyClass() const
{
	return EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
}

// Gets a random place to spawn an enemy
FVector AGameManager::GetRandomLocation(FVector PreviousSpawn) const
{
	float z = PlayerPawn->GetActorLocation().Z;
	FVector RandomLocation;
	if (PreviousSpawn.IsZero())
	{
		do 
		{
			RandomLocation = GetRandomLocationFromReferencePlane();
			RandomLocation.Z = z;

		} while (CalcDistance(PreviousSpawn,RandomLocation)<600);
	}
	else
	{
		RandomLocation = GetRandomLocationFromReferencePlane();
		RandomLocation.Z = z;
	}
	

	return RandomLocation;
}

float AGameManager::CalcDistance(FVector Position1, FVector Position2) const
{
	float x, y, z;
	x = Position1.X - Position2.X;
	x = x * x;
	y = Position1.Y - Position2.Y;
	y = y * y;
	z = Position1.Z - Position2.Z;
	z = z * z;

	return FMath::Sqrt(x + y + z);
}

FVector AGameManager::GetRandomLocationFromReferencePlane() const
{
	FVector RandomLocation;
	FVector Origin;
	FVector BoundsExtent;
	ReferencePlane->GetActorBounds(false, Origin, BoundsExtent);

	RandomLocation = FMath::RandPointInBox(FBox::BuildAABB(Origin, BoundsExtent));

	return RandomLocation;
}

void AGameManager::InitializePerks() {
	PerkArray.AddUnique(ALifePerk::StaticClass());
	PerkArray.AddUnique(ALightShotPerk::StaticClass());
	PerkArray.AddUnique(AHeavyShotPerk::StaticClass());
}


TSubclassOf<APerk> AGameManager::GetRandomPerk(){
	return PerkArray[FMath::RandRange(0, PerkArray.Num() - 1)];
}


void AGameManager::DropPowerUp(FVector SpawnLocation) {

	if (FMath::RandRange(1, 100)<=DropRatio) 
	{
		TSubclassOf<APerk> Perk = GetRandomPerk();
		GetWorld()->SpawnActor(Perk, &SpawnLocation);
	}
}

