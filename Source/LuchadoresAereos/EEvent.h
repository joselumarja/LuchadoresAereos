// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EEvent.generated.h"

UENUM()
enum class EEvent : uint8
{
	EVENT_HIT,
	EVENT_LIGHTENEMY_KILLED,
	EVENT_MEDIUMENEMY_KILLED,
	EVENT_TANKENEMY_KILLED
};