// Fill out your copyright notice in the Description page of Project Settings.

#include "ShotState.h"
#include "Enemy.h"

void UShotState::Enter(IEnemyState& From, AEnemy& Enemy)
{

}

void UShotState::Update(AEnemy& Enemy)
{
	Enemy.Dodge();
}


