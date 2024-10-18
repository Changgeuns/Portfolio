// Fill out your copyright notice in the Description page of Project Settings.
#include "TFT_AnimInstance_IY.h"
#include "TFT_Creature.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_IY::UTFT_AnimInstance_IY()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Inyong/IY_AnimMontage_Test.IY_AnimMontage_Test'"));
	if (am.Succeeded())
	{
		_qSkillMontage = am.Object;
	}
}

void UTFT_AnimInstance_IY::NativeInitializeAnimation()
{
}

void UTFT_AnimInstance_IY::NativeUpdateAnimation(float DeltaSeconds)
{
	ATFT_Creature* myCharacter = Cast<ATFT_Creature>(TryGetPawnOwner());
	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();
		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_vertical = _vertical + (myCharacter->_vertical - _vertical) * DeltaSeconds;
		_horizontal = _horizontal + (myCharacter->_horizontal - _horizontal) * DeltaSeconds;
		_isDead = (myCharacter->GetCurHp() <= 0);
		_isDashing = (myCharacter->isDashing);
		_isAirborne = (myCharacter->GetCurState(StateType::Airborne));
		_isStun = (myCharacter->GetCurState(StateType::Stun));
		_isSlow = (myCharacter->GetCurState(StateType::Slow));
	}
}

void UTFT_AnimInstance_IY::PlayQ_SkillMontage()
{
	if (!Montage_IsPlaying(_qSkillMontage))
	{
		Montage_Play(_qSkillMontage);
	}
}

void UTFT_AnimInstance_IY::JumpToSection(int32 sectionIndex)
{
}

void UTFT_AnimInstance_IY::AnimNotify_DashEnd()
{
	_dashEndDelegate.Broadcast();
}

void UTFT_AnimInstance_IY::AnimNotify_AttackHit()
{
	_attackHitDelegate.Broadcast();
}

void UTFT_AnimInstance_IY::AnimNotify_StunEnd()
{
	_stunEndDelegate.Broadcast();
}
