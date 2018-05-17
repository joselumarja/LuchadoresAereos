// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyState.h"
#include "FindPlayerState.generated.h"

class AEnemy;

UCLASS()
class LUCHADORESAEREOS_API UFindPlayerState : public UObject, public IEnemyState
{
	GENERATED_BODY()
	
public:
	void Enter(IEnemyState& From, AEnemy& Enemy) override;
	void Update(AEnemy& Enemy) override;
	
	
};
