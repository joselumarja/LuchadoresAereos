// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "LuchadoresAereosPawn.h"
#include "Bullet.h"
#include "LightBullet.h"
#include "HeavyAmo.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameManager.h"

const FName ALuchadoresAereosPawn::MoveForwardBinding("MoveForward");
const FName ALuchadoresAereosPawn::MoveRightBinding("MoveRight");
const FName ALuchadoresAereosPawn::FireForwardBinding("FireForward");
const FName ALuchadoresAereosPawn::FireRightBinding("FireRight");


ALuchadoresAereosPawn::ALuchadoresAereosPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->RelativeRotation = FRotator(-80.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	
	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm
	
	OnActorHit.AddDynamic(this, &ALuchadoresAereosPawn::OnHit);

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	bCanFire = true;
	bInvulnerability = false;
	InvulnerabilityTime = 3.0f;
	SetNormalShotState();
}

void ALuchadoresAereosPawn::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AGameManager>ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (FString(TEXT("GameManager_1")).Equals(ActorItr->GetName()))
		{
			//finding manager
			Manager = *ActorItr;
		}
	}
	
	World = GetWorld();
}

void ALuchadoresAereosPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	//PlayerInputComponent->BindAxis(FireRightBinding);

}

void ALuchadoresAereosPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		// No rotation on Z axis
		const FRotator NewRotation(0,0,0);
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

void ALuchadoresAereosPawn::FireShot(FVector FireDirection)
{
	// If we it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			if (World != NULL)
			{
				switch (ShotMode)
				{
					case PlayerShot::Standar:
						World->SpawnActor<ABullet>(SpawnLocation, FireRotation);
						break;
					case PlayerShot::Light:
						World->SpawnActor<ALightBullet>(SpawnLocation, FireRotation);
						break;
					case PlayerShot::Heavy:
						World->SpawnActor<AHeavyAmo>(SpawnLocation, FireRotation);
						break;
				}
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ALuchadoresAereosPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void ALuchadoresAereosPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void ALuchadoresAereosPawn::InvulnerabilityTimerExpired()
{
	bInvulnerability = false;
	//quitar las texturas de la invulnerabilidad
}

void ALuchadoresAereosPawn::SetInvulnerability()
{
	bInvulnerability = true;
	//añadir aqui un cambio de texturas o algo asi
	World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityExpired, this, &ALuchadoresAereosPawn::InvulnerabilityTimerExpired, InvulnerabilityTime);
}

void ALuchadoresAereosPawn::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bInvulnerability && (OtherActor != NULL) && OtherActor->IsA(ALuchadoresAereosProjectile::StaticClass()))
	{

		Manager->UpdateLives();
		SetNormalShotState();
		SetInvulnerability();
	}
}

void ALuchadoresAereosPawn::SetNormalShotState()
{
	ShotMode = PlayerShot::Standar;
	FireRate = 0.3f;
}

void ALuchadoresAereosPawn::SetHeavyShotState()
{
	ShotMode = PlayerShot::Heavy;
	FireRate = 0.7f;
}

void ALuchadoresAereosPawn::SetLightShotState()
{
	ShotMode = PlayerShot::Light;
	FireRate = 0.1f;
}


