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

	FORCEINLINE bool operator<(const FSaveGameStruct &Other) const
	{
		return Score > Other.Score;
	}

	FORCEINLINE bool operator==(const FSaveGameStruct &Other) const
	{
		return Score == Other.Score;
	}

};