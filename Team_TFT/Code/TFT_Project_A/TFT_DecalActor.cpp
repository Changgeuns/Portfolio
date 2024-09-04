// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_DecalActor.h"

#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "TFT_Effect_Manager.h"
#include "TFT_Player.h"
#include "Engine/DamageEvents.h"
#include "TFT_GameInstance.h"

ATFT_DecalActor::ATFT_DecalActor()
{
	PrimaryActorTick.bCanEverTick = true;
	_delayTime = -1.0f;
	_runTime = 0.0f;
}

void ATFT_DecalActor::BeginPlay()
{
	Super::BeginPlay();


	_runTime = 0.0f;
	FVector scale = FVector(1.0f, 0.0f, 0.0f);
	_bisPlay = true;
	_fieldAttackDelegate.AddUObject(this, &ATFT_DecalActor::DeActiveEvent);
}

void ATFT_DecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_delayTime == 0.0f || _bisPlay == false)
		return;

	FVector curscale = GetActorScale();

	if (_runTime > _delayTime && _delayTime > 0.0f)
	{
		_fieldAttackDelegate.Broadcast(GetActorLocation());
		_runTime = 0.0f;
		curscale.Y = 0.0f;
		curscale.Z = 0.0f;

		SetActorScale3D(curscale);

		return;
	}

	_runTime += DeltaTime;
	curscale.Y = (_runTime / _delayTime) * _areaRadius;
	curscale.Z = (_runTime / _delayTime) * _areaRadius;

	SetActorScale3D(curscale);
}

void ATFT_DecalActor::Active(FVector location)
{
	_bisPlay = true;
	SetActorLocation(location);
}

void ATFT_DecalActor::DeActiveEvent(FVector location)
{
	_bisPlay = false;
    TArray<FHitResult> HitResults; 
    FVector DecalLocation = GetActorLocation();
    float Radius = _areaRadius;

   
    UWorld* World = GetWorld();
    if (World)
    {
        FCollisionShape CollisionShape;
        CollisionShape.SetSphere(Radius);

        bool bOverlap = World->SweepMultiByChannel(
            HitResults,  
            DecalLocation,
            DecalLocation,
            FQuat::Identity,
            ECC_Pawn,  
            CollisionShape
        );

        if (bOverlap)
        {
            for (FHitResult& Hit : HitResults)
            {
                
                AActor* HitActor = Hit.GetActor();
                if (HitActor)
                {
                    
                    ATFT_Player* Player = Cast<ATFT_Player>(HitActor);
                    if (Player)
                    {
                        
                        float DamageAmount = 100.0f;  
                        Player->TakeDamage(DamageAmount, FDamageEvent(), GetInstigatorController(), this);
                    }
                }
            }
        }
    }

	EffectManager->Play("P_Explosion", 0, location);
}
