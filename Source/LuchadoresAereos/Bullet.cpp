// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"

ABullet::ABullet():Super()
{

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ALuchadoresAereosProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	ProjectileMesh->bForceNavigationObstacle = true;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

													  // Die after 0.1 seconds by default
	InitialLifeSpan = 1.0f;

	Damage = 10;
}


