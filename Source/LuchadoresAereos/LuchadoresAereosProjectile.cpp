// Copyright 1998-2017 Epic Games, Inc. All Rights Reserve

#include "LuchadoresAereosProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



ALuchadoresAereosProjectile::ALuchadoresAereosProjectile() 
{
	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));//hay que incluir las particulas en el proyecto todavia
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

	if ((OtherActor != NULL) && OtherActor->IsA(ALuchadoresAereosProjectile::StaticClass()))
	{
		uint8 HitEnergy;
		HitEnergy=(Cast<ALuchadoresAereosProjectile>(OtherActor))->GetEnergy();
		UpdateEnergy(HitEnergy);
	}

	Destroy();
}

void ALuchadoresAereosProjectile::UpdateEnergy(uint8 HitEnergy)
{
	Energy -= HitEnergy;

	if (Energy <= 0) 
	{
		Destroy();
	}

}