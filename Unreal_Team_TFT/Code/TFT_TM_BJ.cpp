// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TM_BJ.h"

#include "TFT_MeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Components/WidgetComponent.h"

ATFT_TM_BJ::ATFT_TM_BJ()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/BluePrint/Player/Mesh/SKM_Manny_Simple_BJ.SKM_Manny_Simple_BJ'");
}

void ATFT_TM_BJ::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceBJ = Cast<UTFT_AnimInstance_BJ>(GetMesh()->GetAnimInstance());
	if (_animInstanceBJ->IsValidLowLevel())
	{

	}
}

void ATFT_TM_BJ::BeginPlay()
{
	Super::BeginPlay();
}

void ATFT_TM_BJ::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TM_BJ::PlayAttack(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _animInstanceBJ != nullptr)
	{
		GetCharacterMovement()->DisableMovement();

		_animInstanceBJ->PlayAttackMontage();
		_isAttcking = true;

		FOnMontageEnded MontageEndedDelegate;
		MontageEndedDelegate.BindUObject(this, &ATFT_TM_BJ::OnAttackMontageEnded);
		_animInstanceBJ->Montage_SetEndDelegate(MontageEndedDelegate, _animInstanceBJ->GetCurrentActiveMontage());
	}
}

void ATFT_TM_BJ::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	_isAttcking = false;
}

