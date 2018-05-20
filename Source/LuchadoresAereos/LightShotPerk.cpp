// Fill out your copyright notice in the Description page of Project Settings.

#include "LightShotPerk.h"

ALightShotPerk::ALightShotPerk():Super()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Testeo/SM_MERGED_health_pack_Cube2_33.SM_MERGED_health_pack_Cube2_33"));
	
	FVector Scale = FVector(1.0f);
	// Create mesh component for the projectile sphere
	PerkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightShotPerk"));
	PerkMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	PerkMesh->SetupAttachment(RootComponent);
	PerkMesh->SetWorldScale3D(Scale * 0.3f);
	PerkMesh->BodyInstance.SetCollisionProfileName("LightShotPerk");
	PerkMesh->OnComponentHit.AddDynamic(this, &APerk::OnHit);		// set up a notification for when this component hits something
	RootComponent = PerkMesh;
}

void ALightShotPerk::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == PlayerPawn)
	{
		PlayerPawn->SetLightShotState();
		Destroy();
	}
}


