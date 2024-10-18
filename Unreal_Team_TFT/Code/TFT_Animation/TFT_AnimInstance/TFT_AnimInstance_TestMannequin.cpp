// Fill out your copyright notice in the Description page of Project Settings.
#include "TFT_AnimInstance_TestMannequin.h"
#include "TFT_Creature.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimMontage.h"

UTFT_AnimInstance_TestMannequin::UTFT_AnimInstance_TestMannequin()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> esm
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Dohun_lk/Animations/Jump_Attack.Jump_Attack'"));
	if (esm.Succeeded())
	{
		_eSkillMontage = esm.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> qsm
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/TestMannequin/TFT_TM_QSkill_AnimMontage.TFT_TM_QSkill_AnimMontage'"));
	if (qsm.Succeeded())
	{
		_qSkillMontage = qsm.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> am
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/Player/Beom/BJ_Anim_melee_attack.BJ_Anim_melee_attack'"));
	if (am.Succeeded())
	{
		_attackMontage = am.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am2
	(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/TestMannequin/TM_2hand/CG_Montage_NomalAttack.CG_Montage_NomalAttack'"));
	if (am2.Succeeded())
	{
		_attackMontage2hand = am2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SprintMontageObj(TEXT("/Script/Engine.AnimMontage'/Game/BluePrint/animation/TestMannequin/TFT_TM_Running.TFT_TM_Running'"));
	if (SprintMontageObj.Succeeded())
	{
		SprintMontage = SprintMontageObj.Object;
	}
}

void UTFT_AnimInstance_TestMannequin::NativeInitializeAnimation()
{

}

void UTFT_AnimInstance_TestMannequin::NativeUpdateAnimation(float DeltaSeconds)
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
	}
}

void UTFT_AnimInstance_TestMannequin::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UTFT_AnimInstance_TestMannequin::PlayE_SkillMontage()
{
	if (!Montage_IsPlaying(_eSkillMontage))
	{
		Montage_Play(_eSkillMontage);
	}
}

void UTFT_AnimInstance_TestMannequin::PlayQ_SkillMontage()
{
	if (!Montage_IsPlaying(_qSkillMontage))
	{
		Montage_Play(_qSkillMontage);
	}
}

void UTFT_AnimInstance_TestMannequin::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_attackMontage))
	{
		Montage_Play(_attackMontage);
	}
}

void UTFT_AnimInstance_TestMannequin::PlayAttackMontage2Hend()
{
	if (!Montage_IsPlaying(_attackMontage2hand))
	{
		Montage_Play(_attackMontage2hand);
	}
}

void UTFT_AnimInstance_TestMannequin::AnimNotify_DashEnd()
{
	_dashEndDelegate.Broadcast();
}

void UTFT_AnimInstance_TestMannequin::AnimNotify_AttackStart()
{
	_attackStartDelegate.Broadcast();
}

void UTFT_AnimInstance_TestMannequin::AnimNotify_AttackHit()
{
	_attackHitDelegate.Broadcast();
}

void UTFT_AnimInstance_TestMannequin::AnimNotify_AttackHit_Q()
{
	_attackHit_QDelegate.Broadcast();
}

void UTFT_AnimInstance_TestMannequin::PlaySprintMontage()
{
	if (!Montage_IsPlaying(SprintMontage))
	{
		Montage_Play(SprintMontage, 1.0f);
	}
}

void UTFT_AnimInstance_TestMannequin::StopSprintMontage()
{
	if (Montage_IsPlaying(SprintMontage))
	{
		Montage_Stop(0.2f, SprintMontage);
	}
}
