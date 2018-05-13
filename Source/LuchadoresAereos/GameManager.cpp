// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Engine.h"

// Sets default values
AGameManager::AGameManager():Lives(3),Seconds(200)
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
	World->GetTimerManager().SetTimer(ClockTimer, this, &AGameManager::Clock, 1.0f);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AGameManager::UpdateLives()
{
	if (--Lives == 0)
	{
		GameOver();
	}
	HUD->UpdateLives(Lives);
}
void AGameManager::GameOver()
{

}
