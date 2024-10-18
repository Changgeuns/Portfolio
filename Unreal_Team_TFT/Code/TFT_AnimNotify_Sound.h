// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "TFT_AnimNotify_Sound.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_AnimNotify_Sound : public UAnimNotify
{
	GENERATED_BODY()
	
public:
  
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    FString SoundName;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    FVector SoundLocationOffset;

   
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    FRotator SoundRotationOffset;
};
