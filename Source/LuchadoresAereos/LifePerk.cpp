// Fill out your copyright notice in the Description page of Project Settings.

#include "LifePerk.h"

ALifePerk::ALifePerk():Super()
{

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Testeo/SM_MERGED_Cube_2.SM_MERGED_Cube_2"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	ConstructorHelpers::FObjectFinder<UMaterial> BaseMaterial(TEXT("/Game/TwinStick/Meshes/GoldMaterial.GoldMaterial"));

	//FVector Scale = FVector(1.0f);
	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InvulnerabilityPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->SetMaterial(0, BaseMaterial.Object);
	PerkMesh->BodyInstance.SetCollisionProfileName("InvulnerabilityPerk");
	OnActorHit.AddDynamic(this, &APerk::OnHit);	// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void ALifePerk::ApplyPerk()
{
		PlayerPawn->SetInvulnerability();
}


