// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "LuchadoresAereosProjectile.generated.h"

UCLASS(config=Game)
class ALuchadoresAereosProjectile : public AActor
{
	GENERATED_BODY()

public:
	ALuchadoresAereosProjectile();

	// Function to handle the projectile hitting something 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	FORCEINLINE uint8 GetDamage() const { return Damage; }

	FORCEINLINE uint8 GetEnergy() const { return Energy; }

	void UpdateEnergy(uint8 HitEnergy);

protected:

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
		TWeakObjectPtr<UParticleSystem> ExplosionParticleSystem;

	UPROPERTY()
		uint8 Damage;

	UPROPERTY()
		uint8 Energy;

};

