// Fill out your copyright notice in the Description page of Project Settings.

#include "HeavyAmo.h"

AHeavyAmo::AHeavyAmo():Super()
{

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeavyAmo"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("HeavyAmo");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ALuchadoresAereosProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;


	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("HeavyAmoMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 500.f;
	ProjectileMovement->MaxSpeed = 500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

													  // Die after 4 seconds by default
	InitialLifeSpan = 4.0f;

	Energy = 30;

	Damage = 50;
}


