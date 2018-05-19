// Fill out your copyright notice in the Description page of Project Settings.

#include "DodgeState.h"
#include "ShotState.h"
#include "FindPlayerState.h"
#include "Enemy.h"

void UDodgeState::Enter(IEnemyState& From, AEnemy& Enemy)
{
	Enemy.bCanDodge = true;
	Enemy.SetTimerDodge();
}

void UDodgeState::Update(AEnemy& Enemy)
{
	if (!Enemy.bCanDodge)
	{
		Enemy.ChangeState(Enemy.FindPlayerState);
	}
	else
	{
		Enemy.Dodge();
	}

}


