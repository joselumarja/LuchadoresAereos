// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perk.h"
#include "HeavyShotPerk.generated.h"


UCLASS()
class LUCHADORESAEREOS_API AHeavyShotPerk : public APerk
{
	GENERATED_BODY()
	
public:

	AHeavyShotPerk();

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
