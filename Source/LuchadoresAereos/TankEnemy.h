// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "UObject/ConstructorHelpers.h"
#include "TankEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LUCHADORESAEREOS_API ATankEnemy : public AEnemy
{
	GENERATED_BODY()
	
	protected:
		ATankEnemy();

		UPROPERTY()
		int Time;

		UPROPERTY()
		float Life;
	

		void UpdateState();

	public:
		virtual void Tick(float DeltaTime) override;
		void Shoot() override;
};
