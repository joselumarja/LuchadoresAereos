// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "MediumEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LUCHADORESAEREOS_API AMediumEnemy : public AEnemy
{
	GENERATED_BODY()
	
public:
	AMediumEnemy();

	virtual void Tick(float DeltaTime) override;
	
	void Dodge() override;

	void Shot() override;

	void FindPlayer() override;
};
