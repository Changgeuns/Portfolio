// Fill out your copyright notice in the Description page of Project Settings.
#include "TFT_AnimInstance_BJ.h"
#include "TFT_Creature.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_BJ::UTFT_AnimInstance_BJ()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Beom/BJ_Anim_melee_attack.BJ_Anim_melee_attack'"));
	if (am.Succeeded())
	{
		_myAnimMontage1 = am.Object;
	}
}

void UTFT_AnimInstance_BJ::NativeInitializeAnimation()
{
}

void UTFT_AnimInstance_BJ::NativeUpdateAnimation(float DeltaSeconds)
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

void UTFT_AnimInstance_BJ::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage1))
	{
		Montage_Play(_myAnimMontage1);
	}

	ATFT_Creature* myCharacter = Cast<ATFT_Creature>(TryGetPawnOwner());
}

void UTFT_AnimInstance_BJ::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}