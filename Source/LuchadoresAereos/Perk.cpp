// Fill out your copyright notice in the Description page of Project Settings.

#include "Perk.h"


// Sets default values
APerk::APerk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Bullet");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &APerk::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void APerk::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<ALuchadoresAereosPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void APerk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerk::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && OtherActor==PlayerPawn)
	{
		
	}

	Destroy();
}