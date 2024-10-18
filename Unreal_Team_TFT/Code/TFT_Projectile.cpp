// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ATFT_Projectile::ATFT_Projectile()
{

	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	_collider->InitCapsuleSize(70, 20);
	_collider->SetupAttachment(_meshCom);


	_meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_meshCom->SetupAttachment(_collider);

	_movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

	RootComponent = _collider;
	

	
	_movementCom->InitialSpeed = 8000.0f;
	_movementCom->MaxSpeed = 8000.0f;
	
	_meshCom->SetRelativeRotation(FRotator(0.f, 90.f, 90.f));
}


void ATFT_Projectile::BeginPlay()
{
	Super::BeginPlay();

}


void ATFT_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector velocity = _movementCom->Velocity;
	if (!velocity.IsNearlyZero())  
	{
		FRotator newRotation = velocity.Rotation();
		SetActorRotation(newRotation);  
	}

	
	

}

void ATFT_Projectile::FireInDirection(const FVector& ShootDirection)
{


	_movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;
}

