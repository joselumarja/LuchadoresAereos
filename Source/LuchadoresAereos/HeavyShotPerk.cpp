// Fill out your copyright notice in the Description page of Project Settings.

#include "HeavyShotPerk.h"

AHeavyShotPerk::AHeavyShotPerk():Super()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeavyShotPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->BodyInstance.SetCollisionProfileName("HeavyShotPerk");
	PerkMesh->OnComponentHit.AddDynamic(this, &APerk::OnHit);		// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void AHeavyShotPerk::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && OtherActor == PlayerPawn)
	{
		PlayerPawn->SetHeavyShotState();
		Destroy();
	}
}
