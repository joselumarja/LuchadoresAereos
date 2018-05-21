// Copyright 1998-2017 Epic Games, Inc. All Rights Reserve

#include "LuchadoresAereosProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



ALuchadoresAereosProjectile::ALuchadoresAereosProjectile() 
{
	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}
}

void ALuchadoresAereosProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && OtherActor->IsA(AEnemy::StaticClass()))
	{
		(Cast<AEnemy>(OtherActor))->UpdateLife(Damage);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), GetActorLocation());
		Destroy();
	}

	else 
	{
		Destroy();
	}	
}

