// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LuchadoresAereosGameMode.h"
#include "LuchadoresAereosPawn.h"

ALuchadoresAereosGameMode::ALuchadoresAereosGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ALuchadoresAereosPawn::StaticClass();
}

