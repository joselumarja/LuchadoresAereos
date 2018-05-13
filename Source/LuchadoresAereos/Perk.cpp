// Fill out your copyright notice in the Description page of Project Settings.

#include "Perk.h"


// Sets default values
APerk::APerk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

