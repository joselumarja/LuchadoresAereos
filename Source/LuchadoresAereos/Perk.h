// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "LuchadoresAereosPawn.h"
#include "Perk.generated.h"

UCLASS(Abstract)
class LUCHADORESAEREOS_API APerk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PerkMesh;

	UPROPERTY()
	ALuchadoresAereosPawn* PlayerPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) PURE_VIRTUAL(APerk::OnHit, );

	
	
};
