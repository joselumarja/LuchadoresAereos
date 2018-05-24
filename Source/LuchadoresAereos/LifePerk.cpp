// Fill out your copyright notice in the Description page of Project Settings.

#include "LifePerk.h"

ALifePerk::ALifePerk():Super()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Testeo/SM_MERGED_Cube_2.SM_MERGED_Cube_2"));

	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InvulnerabilityPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetWorldScale3D(FVector(0.15, 0.15, 0.15));
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->BodyInstance.SetCollisionProfileName("InvulnerabilityPerk");
	OnActorHit.AddDynamic(this, &APerk::OnHit);	// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void ALifePerk::ApplyPerk()
{
		PlayerPawn->SetInvulnerability();
}


