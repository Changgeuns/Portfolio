// Fill out your copyright notice in the Description page of Project Settings.
#include "TFT_AnimInstance_CG.h"
#include "TFT_TM_CG.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_CG::UTFT_AnimInstance_CG()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/ChangGeun/CG_Montage_NomalAttack.CG_Montage_NomalAttack'"));
	if (am.Succeeded())
	{
		_myAnimMontage_Attack = am.Object;
	}
}

void UTFT_AnimInstance_CG::NativeInitializeAnimation()
{
	_CGtestMannequin = Cast<ATFT_Player>(GetOwningActor());
}

void UTFT_AnimInstance_CG::NativeUpdateAnimation(float DeltaSeconds)
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

void UTFT_AnimInstance_CG::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage_Attack))
	{
		Montage_Play(_myAnimMontage_Attack);
	}
}

void UTFT_AnimInstance_CG::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}
