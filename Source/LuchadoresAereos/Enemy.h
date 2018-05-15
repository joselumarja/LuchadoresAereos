// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LuchadoresAereosPawn.h"
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

private:

	UWorld* World;

	TSubclassOf<AActor> ProjectileClass;

	/* The mesh component */
	/*UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MeshComponent;*/

	UPROPERTY()
	float Life;

	UPROPERTY()
	float Time;

	UPROPERTY()
	int Score;

	UPROPERTY()
	TWeakObjectPtr<APawn> PlayerPawn;

	//AGameManager* Manager;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateLife(uint8 Damage);

	//virtual void Shoot()=0;

};
