// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "LightEnemy.generated.h"

class ALightBullet;
UCLASS()
class LUCHADORESAEREOS_API ALightEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:

	ALightEnemy();

	virtual void Tick(float DeltaTime) override;

	void Shot() override;

private:
	uint8 RafagaNumber;

};
