// Fill out your copyright notice in the Description page of Project Settings.

#include "FindPlayerState.h"
#include "DodgeState.h"
#include "ShotState.h"
#include "Enemy.h"

void UFindPlayerState::Enter(IEnemyState& From, AEnemy& Enemy)
{

}

void UFindPlayerState::Update(AEnemy& Enemy)
{

	if (Enemy.DistanceToPlayer() > Enemy.FIELD_OF_VIEW)
	{
		Enemy.FindPlayer();
	}
	else
	{
		Enemy.ChangeState(Enemy.ShotState);
		
	}
	
}



