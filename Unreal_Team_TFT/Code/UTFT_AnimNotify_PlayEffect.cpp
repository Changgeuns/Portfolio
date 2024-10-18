// Fill out your copyright notice in the Description page of Project Settings.


#include "UTFT_AnimNotify_PlayEffect.h"
#include "TFT_Player.h"
#include "TFT_GameInstance.h"
#include "TFT_Effect_Manager.h"

void UUTFT_AnimNotify_PlayEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ATFT_Player* Player = Cast<ATFT_Player>(MeshComp->GetOwner());
		if (Player)
		{
			
			UTFT_GameInstance* GameInstance = Cast<UTFT_GameInstance>(Player->GetGameInstance());
			if (GameInstance && GameInstance->GetEffectManager())
			{
				
				FVector EffectLocation = Player->GetActorLocation() + Player->GetActorForwardVector() * 300.0f;  
				FRotator EffectRotation = MeshComp->GetComponentRotation(); 

				
				GameInstance->GetEffectManager()->Play(TEXT("JumpAttack"), 1, EffectLocation, EffectRotation);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("EffectManager or GameInstance is null"));
			}
		}
	}
}
