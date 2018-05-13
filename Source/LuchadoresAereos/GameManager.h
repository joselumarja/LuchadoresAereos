// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUDManager.h"
#include "TimerManager.h"
#include "GameManager.generated.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int Seconds;

	uint8 Lives;

	AHUDManager * HUD;

	FTimerHandle ClockTimer;
	
	UWorld* World;
};
