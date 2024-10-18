// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AnimNotify_Sound.h"
#include "TFT_Player.h"
#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"
#include "Kismet/GameplayStatics.h"

void UTFT_AnimNotify_Sound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        ATFT_Player* Player = Cast<ATFT_Player>(MeshComp->GetOwner());
        if (Player)
        {
            UTFT_GameInstance* GameInstance = Cast<UTFT_GameInstance>(Player->GetGameInstance());
            if (GameInstance && GameInstance->GetSoundManager())
            {
                FVector SoundLocation = Player->GetActorLocation() + SoundLocationOffset;
                FRotator SoundRotation = Player->GetActorRotation() + SoundRotationOffset;

               
                GameInstance->GetSoundManager()->Play("JumpAttack", SoundLocation, SoundRotation);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("SoundManager or GameInstance is null"));
            }
        }
    }
}
