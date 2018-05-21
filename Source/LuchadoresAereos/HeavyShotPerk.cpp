// Fill out your copyright notice in the Description page of Project Settings.

#include "HeavyShotPerk.h"

AHeavyShotPerk::AHeavyShotPerk():Super()
{

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Testeo/SM_MERGED_health_pack_Cube3_54.SM_MERGED_health_pack_Cube3_54'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	FVector Scale = FVector(1.0f);
	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeavyShotPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->SetWorldScale3D(Scale * 0.2f);
	PerkMesh->BodyInstance.SetCollisionProfileName("HeavyShotPerk");
	OnActorHit.AddDynamic(this, &APerk::OnHit);		// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void AHeavyShotPerk::ApplyPerk()
{
		PlayerPawn->SetHeavyShotState();
}

