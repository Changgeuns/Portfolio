// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AreaDamage.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"


ATFT_AreaDamage::ATFT_AreaDamage()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void ATFT_AreaDamage::BeginPlay()
{
	Super::BeginPlay();
	
	ApplyDamage();

    GetWorld()->GetTimerManager().SetTimer(LifetimeTimerHandle, this, &ATFT_AreaDamage::OnLifetimeExpired, Lifetime, false);

}


void ATFT_AreaDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_AreaDamage::ApplyDamage()
{
    FVector Location = GetActorLocation();
    TArray<AActor*> IgnoredActors;

    TArray<FHitResult> HitResults;
    FCollisionShape CollisionShape;
    CollisionShape.SetSphere(DamageRadius);

   
    GetWorld()->SweepMultiByChannel(HitResults, Location, Location, FQuat::Identity, ECC_GameTraceChannel1, CollisionShape);

    for (const FHitResult& Hit : HitResults)
    {
        if (AActor* HitActor = Hit.GetActor())
        {
            UGameplayStatics::ApplyDamage(HitActor, DamageAmount, GetInstigatorController(), this, UDamageType::StaticClass());
        }
    }


}

void ATFT_AreaDamage::OnLifetimeExpired()
{
    UE_LOG(LogTemp, Warning, TEXT("Lifetime expired, destroying actor."));
    Destroy();
}