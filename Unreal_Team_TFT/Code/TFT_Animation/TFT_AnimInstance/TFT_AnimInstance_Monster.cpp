// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AnimInstance_Monster.h"
#include "TFT_Player.h"
#include "TFT_Creature.h"
#include "TFT_Monster.h"
#include "TFT_Monster_Boss.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_Monster::UTFT_AnimInstance_Monster()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/MonsterAttackDelay/TFT_AnimMontage_Boss.TFT_AnimMontage_Boss'"));

	if (am.Succeeded())
	{
		_myAnimMontage = am.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> sm
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/SMASH_MONTAGE.SMASH_MONTAGE'"));

	if (sm.Succeeded())
	{
		_skillMontage = sm.Object;
	}
}

void UTFT_AnimInstance_Monster::NativeUpdateAnimation(float DeltaSeconds)
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

void UTFT_AnimInstance_Monster::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage))
	{
		Montage_Play(_myAnimMontage);

		ATFT_Monster* myCharacter = Cast<ATFT_Monster>(TryGetPawnOwner());
		if (myCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Pawn Owner Cast Successful"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Pawn Owner Cast Failed"));
		}
		
	}
}

void UTFT_AnimInstance_Monster::PlaySkillMontage()
{
	if (!Montage_IsPlaying(_skillMontage))
	{
		Montage_Play(_skillMontage);

		ATFT_Monster* myCharacter = Cast<ATFT_Monster>(TryGetPawnOwner());
		if (myCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skill Cast Successful"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Skill Cast Failed"));
		}

	}
}


void UTFT_AnimInstance_Monster::DelegateTest()
{
	UE_LOG(LogTemp, Warning, TEXT("Delegate Test"));
}

void UTFT_AnimInstance_Monster::DelegateTest2(int32 hp, int32 mp)
{
	UE_LOG(LogTemp, Warning, TEXT("HP : %d , MP : %d"), hp, mp);
}

void UTFT_AnimInstance_Monster::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UTFT_AnimInstance_Monster::AnimNotify_AttackStart()
{
	_attackStartDelegate.Broadcast();
}

void UTFT_AnimInstance_Monster::AnimNotify_AttackHit()
{
	_attackHitDelegate.Broadcast();
}

void UTFT_AnimInstance_Monster::AnimNotify_DeathStart()
{
	_deathStartDelegate.Broadcast();
}

void UTFT_AnimInstance_Monster::AnimNotify_DeathEnd()
{
	_deathEndDelegate.Broadcast();
}

void UTFT_AnimInstance_Monster::AnimNotify_Boss_DeathEnd()
{
	_bossDeathEndDelegate.Broadcast();
}
