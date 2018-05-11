// Copyright 1998-2017 Epic Games, Inc. All Rights Reserve

#include "LuchadoresAereosProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "EngineMinimal.h"

ALuchadoresAereosProjectile::ALuchadoresAereosProjectile() 
{
	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));//hay que incluir las particulas en el proyecto todavia
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}

	//TODO EL CODIGO RESTANTE DEL METODO HAY QUE MOVERLO A LAS CLASES HIJAS Y MODIFICARLO EN CADA UNA

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ALuchadoresAereosProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

//MI POLLA MORENA

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