// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "TankEnemy.generated.h"

class AHeavyAmo;
UCLASS()
class LUCHADORESAEREOS_API ATankEnemy : public AEnemy
{
	GENERATED_BODY()
	
	public:
		ATankEnemy();

		virtual void Tick(float DeltaTime) override;

		void Dodge() override;

		void Shot() override;

};
