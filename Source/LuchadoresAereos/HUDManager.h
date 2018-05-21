// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "HUDManager.generated.h"

UCLASS()
class LUCHADORESAEREOS_API AHUDManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHUDManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<class UUserWidget> HUDWidget;

	void UpdateSeconds(int Seconds);

	void UpdateLives(int Lives);

	void UpdateScore(int Score);

	void UpdateEnemiesKilled(int Enemies);

	void SetInvencibility(bool value);

	void SetLightShot(bool value);
	
	void SetHeavyShot(bool value);

private:

	// Variable to hold the widget after creating it
	TWeakObjectPtr<class UUserWidget> pHUDWidget;

	TWeakObjectPtr<class UTextBlock> pScore;

	TWeakObjectPtr<class UTextBlock> pKilledEnemies;

	TWeakObjectPtr<class UTextBlock> pTimeInRound;

	TWeakObjectPtr<class UTextBlock> pLives;


	TWeakObjectPtr<class UImage> pInvPerk;

	TWeakObjectPtr<class UImage> pLightPerk;

	TWeakObjectPtr<class UImage> pHeavyPerk;


};
