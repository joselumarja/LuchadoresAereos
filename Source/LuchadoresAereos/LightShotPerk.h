// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "LightShotPerk.generated.h"

UCLASS()
class LUCHADORESAEREOS_API ALightShotPerk : public APerk
{
	GENERATED_BODY()
	
public:

	ALightShotPerk();
	
	void ApplyPerk() override;
};