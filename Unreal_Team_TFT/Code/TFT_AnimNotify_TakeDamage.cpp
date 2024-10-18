// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AnimNotify_TakeDamage.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "Components/SkeletalMeshComponent.h"
#include "TFT_TM_DH.h"
#include "TFT_Player.h"
#include "Engine/DamageEvents.h"

void UTFT_AnimNotify_TakeDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    if (MeshComp && MeshComp->GetOwner())
    {
        DealDamage(MeshComp);  
    }
}

void UTFT_AnimNotify_TakeDamage::DealDamage(USkeletalMeshComponent* MeshComp)
{
    ATFT_Player* Character = Cast<ATFT_Player>(MeshComp->GetOwner());
    if (Character)
    {
        FHitResult hitResult;
        FCollisionQueryParams params(NAME_None, false, Character);

        float attackRange = 500.0f;   
        float attackRadius = 100.0f;  

       
        bool bResult = Character->GetWorld()->SweepSingleByChannel
        (
            hitResult,
            Character->GetActorLocation(),
            Character->GetActorLocation() + Character->GetActorForwardVector() * attackRange,
            FQuat::Identity,
            ECollisionChannel::ECC_GameTraceChannel9,
            FCollisionShape::MakeSphere(attackRadius),
            params
        );

        FVector vec = Character->GetActorForwardVector() * attackRange;
        FVector center = Character->GetActorLocation() + vec * 0.5f;
        FColor drawColor = FColor::Green;  

        if (bResult && hitResult.GetActor()->IsValidLowLevel())
        {
            drawColor = FColor::Red;  

            
            FDamageEvent damageEvent;
            hitResult.GetActor()->TakeDamage(DamageAmount, damageEvent, Character->GetController(), Character);
        }

        
        DrawDebugSphere(Character->GetWorld(), center, attackRadius, 20, drawColor, false, 2.0f);
    }
}
