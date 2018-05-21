// Fill out your copyright notice in the Description page of Project Settings.

#include "Perk.h"


// Sets default values
APerk::APerk()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 10.0f;
}

// Called when the game starts or when spawned
void APerk::BeginPlay()
{
	Super::BeginPlay();
	for (TActorIterator<ALuchadoresAereosPawn>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("TP_TwinStickPawn_1")).Equals(ActorItr->GetName()))
		{
			//finding pawn
			PlayerPawn = *ActorItr;
		}
	}
}

// Called every frame
void APerk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Movement = FVector(0.f,0.f,0.f);
	const FRotator NewRotation(0, DeltaTime, 0);
	FHitResult Hit(1.f);
	RootComponent->MoveComponent(Movement, NewRotation, true);

	if (Hit.IsValidBlockingHit())
	{
		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		RootComponent->MoveComponent(Deflection, NewRotation, true);
	}
}

void APerk::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && OtherActor->IsA(ALuchadoresAereosPawn::StaticClass()))
	{
		ApplyPerk();
		Destroy();
	}
}
