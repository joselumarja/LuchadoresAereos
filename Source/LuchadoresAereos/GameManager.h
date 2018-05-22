// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUDManager.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Perk.h"
#include "LifePerk.h"
#include "HeavyShotPerk.h"
#include "LightShotPerk.h"
#include "LightEnemy.h"
#include "MediumEnemy.h"
#include "TankEnemy.h"
#include "GameManager.generated.h"

class ALuchadoresAereosPawn;

UCLASS()
class LUCHADORESAEREOS_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	void Clock();

	void SumSeconds(uint8 ExtraSeconds);

	void GameOver();

	void UpdateLives();

	void UpdateScore(uint8 ExtraScore);

	void SpawnEnemies(int Enemies);
	
	void UpdateEnemyKilled();

	void InitializeSpawnEnemies();

	void InitializePerks();

	TSubclassOf<AEnemy> GetRandomEnemyClass() const;

	TSubclassOf<APerk> GetRandomPerk();

	void DropPowerUp(FVector SpawnLocation);

	void EnemyKilled(uint8 Score, uint8 ExtraTime);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int DropRatio;

	int Score;

	int Seconds;

	int EnemiesKilled;

	bool Spawn = true;

	uint8 Lives;

	uint8 EnemiesAlived;

	uint8 EnemiesKilledPerRound;

	uint8 Round;

	AHUDManager * HUD;

	FTimerHandle ClockTimer;
	
	UWorld* World;

	TArray<TSubclassOf<AEnemy>> EnemyClasses;

	TArray<TSubclassOf<APerk>> PerkArray;

	FVector GetRandomLocation() const;

	TWeakObjectPtr<AActor> ReferencePlane;

	TWeakObjectPtr<ALuchadoresAereosPawn> PlayerPawn;

};
