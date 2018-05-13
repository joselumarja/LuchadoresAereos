// Fill out your copyright notice in the Description page of Project Settings.

#include "LifePerk.h"

ALifePerk::ALifePerk():Super()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InvulnerabilityPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->BodyInstance.SetCollisionProfileName("InvulnerabilityPerk");
	PerkMesh->OnComponentHit.AddDynamic(this, &APerk::OnHit);		// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void ALifePerk::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && OtherActor == PlayerPawn)
	{
		PlayerPawn->SetInvulnerability();
		Destroy();
	}
}

