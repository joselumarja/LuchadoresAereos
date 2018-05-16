// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuchadoresAereosPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Enemy.generated.h"

UCLASS(Abstract)
class LUCHADORESAEREOS_API AEnemy : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit);
	
	float Life;

	float Time;

	int Score;

	UWorld* World;

	TSubclassOf<AActor> ProjectileClass;

	TWeakObjectPtr<ALuchadoresAereosPawn> PlayerPawn;

	class UStaticMeshComponent* MeshComponent;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateLife(uint8 Damage);

	void Move();
	
	
};
