// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TM_CG.h"

#include "TFT_MeshComponent.h"

#include "Components/WidgetComponent.h"
#include "TFT_HpBar.h"
#include "Particles/ParticleSystemComponent.h"
#include "Blueprint/UserWidget.h"

ATFT_TM_CG::ATFT_TM_CG()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/BluePrint/Player/Mesh/SKM_Manny_Simple_CG.SKM_Manny_Simple_CG'");

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_HpBar_Player_BP.TFT_HpBar_Player_BP_C'"));
	if (HpBar.Succeeded())
	{
		HpBarWidgetClass = HpBar.Class;
	}

	if (HpBarWidgetClass)
	{
		HpBarWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HpBarWidgetClass);
		if (HpBarWidgetInstance)
		{
			HpBarWidgetInstance->AddToViewport();
		}
	}

}

void ATFT_TM_CG::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceCG = Cast<UTFT_AnimInstance_CG>(GetMesh()->GetAnimInstance());
	if (_animInstanceCG->IsValidLowLevel())
	{
		_animInstanceCG->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
	}

	if (HpBarWidgetInstance)
	{

		UTFT_HpBar* HpBar = Cast<UTFT_HpBar>(HpBarWidgetInstance);
		if (HpBar)
		{
			_statCom->_hpChangedDelegate.AddUObject(HpBar, &UTFT_HpBar::SetHpBarValue);
			_statCom->_expChangedDelegate.AddUObject(HpBar, &UTFT_HpBar::SetExpBarValue);
		}
	}
}

void ATFT_TM_CG::BeginPlay()
{
	Super::BeginPlay();

	_statCom->SetLevelAndInit(101);
}

void ATFT_TM_CG::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TM_CG::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	

	if (isPressed && !_isAttacking && _animInstanceCG != nullptr)
	{
		if (auto CGAnimInstance = Cast<UTFT_AnimInstance_CG>(_animInstanceCG))
		{
			CGAnimInstance->PlayAttackMontage();
			_isAttacking = true;

			_curAttackIndex %= 2;
			_curAttackIndex++;

			CGAnimInstance->JumpToSection(_curAttackIndex);
		}

		return;
	}
}
