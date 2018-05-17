// Fill out your copyright notice in the Description page of Project Settings.

#include "FindPlayerState.h"
#include "Enemy.h"

void UFindPlayerState::Enter(IEnemyState& From, AEnemy& Enemy)
{

}

void UFindPlayerState::Update(AEnemy& Enemy)
{
	Enemy.FindPlayer();
}



