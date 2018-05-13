// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"
#include "LuchadoresAereos.h"

#define LOCTEXT_NAMESPACE "MySaveGame"

int32 UMySaveGame::GetIndexName() const
{
	return UserIndex;
}

FString UMySaveGame::GetSlotName()const
{
	return SaveSlotName;
}

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}

FText UMySaveGame::GetRecordNames()const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("Names", "{0}{1}\n"), String, Records[i].PlayerName);
	}

	return String;
}

FText UMySaveGame::GetRecordScores()const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("Scores", "{0}{1}\n"), String, FText::AsNumber(Records[i].Score));
	}

	return String;
}

FText UMySaveGame::GetRecordKilledEnemies()const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("KilledEnemies", "{0}{1}\n"), String,  FText::AsNumber(Records[i].KilledEnemies));
	}

	return String;
}
void UMySaveGame::UpdateRecords(int32 KilledEnemies, FText name, int32 Score)
{
	FSaveGameStruct NewSave= FSaveGameStruct(name, KilledEnemies, Score);
	Records.Add(NewSave);
	Records.Sort();
}

#undef LOCTEXT_NAMESPACE


