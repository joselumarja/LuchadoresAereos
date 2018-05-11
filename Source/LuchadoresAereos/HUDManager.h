// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUDManager.generated.h"

UCLASS()
class AHUDManager : public AActor
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
		TSubclassOf<class UUserWidget> ArchievementWidget;

	void NewRound(int Round);

	void UpdateSeconds();

	void InInterRoundBehaviour();

	void UpdateFails();

	void UpdateScore(int Score);

private:

	// Variable to hold the widget after creating it
	TWeakObjectPtr<class UUserWidget> pHUDWidget;

	TWeakObjectPtr<class UTextBlock> pScore;

	TWeakObjectPtr<class UTextBlock> pRoundText;

	TWeakObjectPtr<class UTextBlock> pPrepareText;

	TWeakObjectPtr<class UTextBlock> pTimeInRound;

	TWeakObjectPtr<class UTextBlock> pNumFails;

	float AccumulatedDeltaTime;

	TArray<FText> PrepareArray;

	TArray<FSlateColor> PrepareColor;

	bool InInterRound;

	uint8 PositionPrepare;

	int SecondsInRound, MinutesInRound;

	int Fails;


};
