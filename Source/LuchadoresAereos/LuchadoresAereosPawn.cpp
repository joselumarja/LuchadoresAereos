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
#include "Materials/MaterialInstance.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameManager.h"

const FName ALuchadoresAereosPawn::MoveForwardBinding("MoveForward");
const FName ALuchadoresAereosPawn::MoveRightBinding("MoveRight");
const FName ALuchadoresAereosPawn::FireForwardBinding("FireForward");


ALuchadoresAereosPawn::ALuchadoresAereosPawn()
{	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Testeo/SM_MERGED_ju-87_body_2.SM_MERGED_ju-87_body_2"));
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GoldMaterial;
		FConstructorStatics()
			: BaseMaterial(TEXT("/Game/TwinStick/PersonajePrincipal/body_material.body_material"))
			, GoldMaterial(TEXT("/Game/TwinStick/Meshes/GoldMaterial.GoldMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	ShipMeshComponent->SetWorldScale3D(FVector(0.07f, 0.07f, 0.07f));
	ShipMeshComponent->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	GoldMaterial = ConstructorStatics.GoldMaterial.Get();

	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	static ConstructorHelpers::FObjectFinder<USoundBase> InvAudio(TEXT("/Game/TwinStick/Audio/Chimo_Bayo_-_Extasy_extano__1080p_-_AudioTrimmer_com___3_.Chimo_Bayo_-_Extasy_extano__1080p_-_AudioTrimmer_com___3_"));
	InvulnerabilitySound = InvAudio.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> HitAudio(TEXT("/Game/TwinStick/Audio/mario-bros_tuberia.mario-bros_tuberia"));
	HitSound = HitAudio.Object;
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

	auto ParticleSystemAsset = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'"));
	if (ParticleSystemAsset.Succeeded())
	{
		ExplosionParticleSystem = ParticleSystemAsset.Object;
	}


	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(140.f, 0.f, 0.f);

	bCanFire = true;
	bInvulnerability = false;
	InvulnerabilityTime = 14.0f;
	HitInvulnerabilityTime = 0.0f;
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
		FRotator NewRotation=GetActorRotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	CheckPosition();
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const FVector FireDirection = FVector(FireForwardValue, 0.f, 0.f);

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
						FVector SpawnLocation2, SpawnLocation3, ActorFordwardVector;
						ActorFordwardVector = GetActorForwardVector();
						SpawnLocation2 = SpawnLocation + ActorFordwardVector * 100;
						SpawnLocation3 = SpawnLocation - ActorFordwardVector * 100;

						World->SpawnActor<AHeavyAmo>(SpawnLocation, FireRotation);
						World->SpawnActor<AHeavyAmo>(SpawnLocation2, FireRotation);
						World->SpawnActor<AHeavyAmo>(SpawnLocation3, FireRotation);
						break;
				}
			}

			bCanFire = false;
			// Setting a timer with the fire rate of the shoot
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
	ShipMeshComponent->SetMaterial(0, BaseMaterial);
}

// Changes the material of the player when takes a bullet hit
void ALuchadoresAereosPawn::HitInvulnerabilityExpired()
{
	ShipMeshComponent->SetMaterial(0, BaseMaterial);
	World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ALuchadoresAereosPawn::SetHitInvulnerability, 0.5f);
}

// Changes the material of the player when takes a bullet hit
void ALuchadoresAereosPawn::SetHitInvulnerability()
{
	bInvulnerability = true;
	HitInvulnerabilityTime++;
	if (HitInvulnerabilityTime == 4.0) {
		bInvulnerability = false;
		HitInvulnerabilityTime = 0.0f;
		ShipMeshComponent->SetMaterial(0, BaseMaterial);
	}
	else {
		ShipMeshComponent->SetMaterial(0, GoldMaterial);
		World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityHitExpired, this, &ALuchadoresAereosPawn::HitInvulnerabilityExpired, 0.5f);
	}
}

// Invulnerability method with music 
void ALuchadoresAereosPawn::SetInvulnerability()
{
	bInvulnerability = true;
	ShipMeshComponent->SetMaterial(0, GoldMaterial);
	UGameplayStatics::PlaySoundAtLocation(this, InvulnerabilitySound, GetActorLocation());
	World->GetTimerManager().SetTimer(TimerHandle_InvulnerabilityExpired, this, &ALuchadoresAereosPawn::InvulnerabilityTimerExpired, InvulnerabilityTime);
}

void ALuchadoresAereosPawn::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	
	if ((OtherActor != NULL) && (OtherActor->IsA(ALuchadoresAereosProjectile::StaticClass())) || (OtherActor->IsA(AEnemy::StaticClass())))
	{
		if (!bInvulnerability) 
		{
			Manager->UpdateLives();
			SetNormalShotState();
			SetHitInvulnerability();
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem.Get(), GetActorLocation());
		}
		if (OtherActor->IsA(AEnemy::StaticClass()))
		{
			(Cast<AEnemy>(OtherActor))->NotifyManager(0, 0);
		}
		OtherActor->Destroy();
	}
}

// Changes the position of the player if he is to far from game field
void ALuchadoresAereosPawn::CheckPosition()
{
	if (GetActorLocation().X > 2090.f)
	{
		Manager->UpdateLives();
		SetActorLocation(InitialPosition);
	}
}

// Methods to change the type of player´s shoot
void ALuchadoresAereosPawn::SetNormalShotState()
{
	ShotMode = PlayerShot::Standar;
	FireRate = 0.3f;
}

void ALuchadoresAereosPawn::SetHeavyShotState()
{
	ShotMode = PlayerShot::Heavy;
	FireRate = 0.4f;
}

void ALuchadoresAereosPawn::SetLightShotState()
{
	ShotMode = PlayerShot::Light;
	FireRate = 0.2f;
}


