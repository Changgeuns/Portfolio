// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AnimInstance_Archer.h"
#include "TFT_Player.h"
#include "TFT_Creature.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "TFT_Archer.h"

UTFT_AnimInstance_Archer::UTFT_AnimInstance_Archer()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/TFT_Montage_Archer.TFT_Montage_Archer'"));

	if (am.Succeeded())
	{
		_myAnimMontage = am.Object;
	}
}

void UTFT_AnimInstance_Archer::NativeUpdateAnimation(float DeltaSeconds)
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

void UTFT_AnimInstance_Archer::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage))
	{
		Montage_Play(_myAnimMontage);

		ATFT_Archer* myCharacter = Cast<ATFT_Archer>(TryGetPawnOwner());
		
	}
}

void UTFT_AnimInstance_Archer::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UTFT_AnimInstance_Archer::AnimNotify_AttackStart()
{
	_attackStartDelegate.Broadcast();
}

void UTFT_AnimInstance_Archer::AnimNotify_AttackHit()
{
	_attackHitDelegate.Broadcast();
}

void UTFT_AnimInstance_Archer::AnimNotify_DeathStart()
{
	_deathStartDelegate.Broadcast();
}

void UTFT_AnimInstance_Archer::AnimNotify_DeathEnd()
{
	_deathEndDelegate.Broadcast();
}
