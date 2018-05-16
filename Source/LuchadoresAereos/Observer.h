// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EEvent.h"
#include "Observer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObserver : public UInterface
{
	GENERATED_BODY()
};


class LUCHADORESAEREOS_API IObserver
{
	GENERATED_BODY()

public:
	virtual void OnNotify(EEvent Event) = 0;
	
};
