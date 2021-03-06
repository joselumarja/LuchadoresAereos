// Fill out your copyright notice in the Description page of Project Settings.

#include "LightShotPerk.h"

ALightShotPerk::ALightShotPerk():Super()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Testeo/SM_MERGED_health_pack_Cube2_33.SM_MERGED_health_pack_Cube2_33"));
	
	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightShotPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetWorldScale3D(FVector(0.3, 0.3, 0.3));
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->BodyInstance.SetCollisionProfileName("LightShotPerk");
	OnActorHit.AddDynamic(this, &APerk::OnHit);	// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void ALightShotPerk::ApplyPerk()
{
		PlayerPawn->SetLightShotState();
}

