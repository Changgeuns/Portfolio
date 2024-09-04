// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TeamAI_Archer.h"

#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/DamageEvents.h"

#include "TFT_HpBar.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

#include "TFT_AnimInstance_Archer.h"

#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"

ATFT_TeamAI_Archer::ATFT_TeamAI_Archer()
{
	PrimaryActorTick.bCanEverTick = true;

	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));


	SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Skins/ZechinHuntress/Meshes/Sparrow_ZechinHuntress.Sparrow_ZechinHuntress'");

	_hpbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));

	_hpbarWidget->SetupAttachment(GetMesh());
	_hpbarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpbarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));


	static ConstructorHelpers::FClassFinder<UUserWidget> hpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_HpBar_Nomal_BP.TFT_HpBar_Nomal_BP_C'"));
	if (hpBar.Succeeded())
	{
		_hpbarWidget->SetWidgetClass(hpBar.Class);
	}

}

void ATFT_TeamAI_Archer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance_Archer = Cast<UTFT_AnimInstance_Archer>(GetMesh()->GetAnimInstance());

	if (_animInstance_Archer->IsValidLowLevel())
	{
		_animInstance_Archer->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
		_animInstance_Archer->_attackStartDelegate.AddUObject(this, &ATFT_TeamAI_Archer::AttackStart);
		_animInstance_Archer->_attackHitDelegate.AddUObject(this, &ATFT_TeamAI_Archer::AttackHit);
		_animInstance_Archer->_deathStartDelegate.AddUObject(this, &ATFT_TeamAI_Archer::DeathStart);
		_animInstance_Archer->_deathEndDelegate.AddUObject(this, &ATFT_TeamAI_Archer::Disable);
	}


	_hpbarWidget->InitWidget();
	auto hpBar = Cast<UTFT_HpBar>(_hpbarWidget->GetUserWidgetObject());

	if (hpBar)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UTFT_HpBar::SetHpBarValue);
	}

}

void ATFT_TeamAI_Archer::BeginPlay()
{
	Super::BeginPlay();

	Init();

	_statCom->SetLevelAndInit(22);
}

void ATFT_TeamAI_Archer::Init()
{

}

void ATFT_TeamAI_Archer::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TeamAI_Archer::Attack_AI()
{
	Super::Attack_AI();

	if (_isAttacking == false && _animInstance_Archer != nullptr)
	{
		_animInstance_Archer->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance_Archer->JumpToSection(_curAttackIndex);
	}
}

void ATFT_TeamAI_Archer::AttackStart()
{
	Super::AttackStart();

	SoundManager->Play("TeamAI_Archer_Shoot", GetActorLocation());
}

void ATFT_TeamAI_Archer::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 1000.0f;
	float attackRadius = 20.0f;
	FVector forward = GetActorForwardVector();

	FQuat quat = FQuat::FindBetweenVectors(FVector::UpVector, forward);
	FVector center = GetActorLocation() + forward * attackRange * 0.5f;
	FVector start = GetActorLocation();
	FVector end = start + forward * (attackRange * 0.5f);


	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		start,
		end,
		quat,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);


	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), damageEvent, GetController(), this);
		
	}

}

void ATFT_TeamAI_Archer::DeathStart()
{
	Super::DeathStart();

	SoundManager->Play("TeamAI_Archer_Death", GetActorLocation());

	_animInstance_Archer->_deathStartDelegate.RemoveAll(this);
}

void ATFT_TeamAI_Archer::Disable()
{
	Super::Disable();

	_animInstance_Archer->_deathEndDelegate.RemoveAll(this);
}
