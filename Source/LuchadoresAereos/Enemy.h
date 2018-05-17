// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuchadoresAereosPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Enemy.generated.h"

class IEnemyState;
class AGameManager;
class ALuchadoresAereosProjectile;


UCLASS(Abstract)
class LUCHADORESAEREOS_API AEnemy : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(AActor *SelfActor, AActor *OtherActor, FVector NormalImpulse, const FHitResult &Hit);
	
	float Life;

	float Time;

	int Score;

	UWorld* World;

	TSubclassOf<ALuchadoresAereosProjectile> ProjectileClass;

	TWeakObjectPtr<ALuchadoresAereosPawn> PlayerPawn;

	class UStaticMeshComponent* MeshComponent;

	AGameManager* Manager;

	// The previous state this class comes from
	IEnemyState* OldState;

	// The current state this class is
	IEnemyState* CurrentState;

	// The field of view of the enemy used in the Idle and Watch states mainly
	float FIELD_OF_VIEW;

	float DeltaSeconds;

	float FireRate;

	float MoveSpeed;

	bool bCanFire;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	// Forward-declare state classes and makes them friends of this class
	friend class UDodgeState;
	friend class UFindPlayerState;
	friend class UShotState;

	// Actual states
	UPROPERTY()
		UDodgeState* DodgeState;
	UPROPERTY()
		UFindPlayerState* FindPlayerState;
	UPROPERTY()
		UShotState* ShotState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ShotTimerExpired();

	void UpdateLife(uint8 Damage);

	virtual void Dodge() PURE_VIRTUAL(AEnemy::Dodge, );

	virtual void Shot() PURE_VIRTUAL(AEnemy::Shot, );

	void FindPlayer();

	virtual void ChangeState(const TScriptInterface<IEnemyState>& State);

	float DistanceToPlayer();
};
