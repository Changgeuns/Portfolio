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

	_meshCom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	_movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

	RootComponent = _meshCom;
	_collider->SetupAttachment(_meshCom);

	
	_movementCom->InitialSpeed = 8000.0f;
	_movementCom->MaxSpeed = 8000.0f;
	
}


void ATFT_Projectile::BeginPlay()
{
	Super::BeginPlay();

}


void ATFT_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	SetActorRotation(FRotator(90.0f, 0.0f, 90.0f));
}

void ATFT_Projectile::FireInDirection(const FVector& ShootDirection)
{
	_movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;
}

