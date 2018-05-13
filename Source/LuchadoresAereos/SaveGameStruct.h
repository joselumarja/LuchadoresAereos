// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SaveGameStruct.generated.h"

USTRUCT()
struct FSaveGameStruct
{
	GENERATED_BODY()
public:

	UPROPERTY()
		FText PlayerName;

	UPROPERTY()
		int32 Score;

	UPROPERTY()
		int32 KilledEnemies;

	FSaveGameStruct()
	{
		this->PlayerName = FText();
		this->Score = 0;
		this->KilledEnemies = 0;
	}

	FSaveGameStruct(FText PlayerName, int32 Score, int32 KilledEnemies)
	{
		this->PlayerName = PlayerName;
		this->Score = Score;
		this->KilledEnemies = KilledEnemies;
	}

	FORCEINLINE bool operator<(const FSaveGameStruct &Other) const
	{
		return Score > Other.Score;
	}

	FORCEINLINE bool operator==(const FSaveGameStruct &Other) const
	{
		return Score == Other.Score;
	}

};