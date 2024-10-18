// Fill out your copyright notice in the Description page of Project Settings.
#include "TFT_AnimInstance_DH.h"
#include "TFT_Creature.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_DH::UTFT_AnimInstance_DH()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT(""));
	if (am.Succeeded())
	{
		_myAnimMontage = am.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> esm
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Dohun_lk/Animations/Jump_Attack.Jump_Attack'"));
	if (esm.Succeeded())
	{
		_eSkillMontage = esm.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SprintMontageObj(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Dohun_lk/Animations/DH_Running_Montager.DH_Running_Montager'"));
	if (SprintMontageObj.Succeeded())
	{
		SprintMontage = SprintMontageObj.Object;
	}

}

void UTFT_AnimInstance_DH::NativeInitializeAnimation()
{
}

void UTFT_AnimInstance_DH::NativeUpdateAnimation(float DeltaSeconds)
{
	ATFT_Creature* myCharacter = Cast<ATFT_Creature>(TryGetPawnOwner());
	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();
		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_vertical = _vertical + (myCharacter->_vertical - _vertical) * DeltaSeconds;
		_horizontal = _horizontal + (myCharacter->_horizontal - _horizontal) * DeltaSeconds;
		_isDead = (myCharacter->GetCurHp() <= 0);
	}
}

void UTFT_AnimInstance_DH::PlayAttackMontage()
{
}

void UTFT_AnimInstance_DH::JumpToSection(int32 sectionIndex)
{
}

void UTFT_AnimInstance_DH::PlayE_SkillMontage()
{
	if (!Montage_IsPlaying(_eSkillMontage))
	{
		Montage_Play(_eSkillMontage);
	}
}

void UTFT_AnimInstance_DH::PlaySprintMontage()
{
	if (!Montage_IsPlaying(SprintMontage))
	{
		Montage_Play(SprintMontage, 1.0f);
	}
}

void UTFT_AnimInstance_DH::StopSprintMontage()
{
	if (Montage_IsPlaying(SprintMontage))
	{
		Montage_Stop(0.2f, SprintMontage);
	}
}
