// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "LifePerk.generated.h"

UCLASS()
class LUCHADORESAEREOS_API ALifePerk : public APerk
{
	GENERATED_BODY()
	
public:

	ALifePerk();
	
	void ApplyPerk() override;
};
