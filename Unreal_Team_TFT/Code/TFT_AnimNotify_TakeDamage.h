// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TFT_AnimNotify_TakeDamage.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_AnimNotify_TakeDamage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
    
    void DealDamage(USkeletalMeshComponent* MeshComp);

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DamageAmount = 1000.0f; 
};
