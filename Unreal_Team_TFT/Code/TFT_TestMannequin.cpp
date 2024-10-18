// Fill out your copyright notice in the Description page of Project Settings.

#include "TFT_TestMannequin.h"

#include "TFT_MeshComponent.h"
#include "TFT_InvenComponent.h"

#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "TFT_GameInstance.h"
#include "TFT_UIManager.h"
#include "TFT_SoundManager.h"

#include "TFT_TM_SkillUI.h"

#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"

#include "TFT_Item.h"
#include "TFT_HpBar.h"

ATFT_TestMannequin::ATFT_TestMannequin()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/ControlRig/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'");

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

void ATFT_TestMannequin::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceTM = Cast<UTFT_AnimInstance_TestMannequin>(GetMesh()->GetAnimInstance());
	if (_animInstanceTM->IsValidLowLevel())
	{
		_animInstanceTM->_attackStartDelegate.AddUObject(this, &ATFT_TestMannequin::AttackStart);
		_animInstanceTM->_attackHitDelegate.AddUObject(this, &ATFT_TestMannequin::AttackHit);
		_animInstanceTM->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
		_animInstanceTM->_dashEndDelegate.AddUObject(this, &ATFT_TestMannequin::DashEnd);
		_animInstanceTM->_attackHit_QDelegate.AddUObject(this, &ATFT_TestMannequin::AttackHit_Q);
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

void ATFT_TestMannequin::BeginPlay()
{
	Super::BeginPlay();

	_statCom->SetLevelAndInit(10);
}

void ATFT_TestMannequin::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TestMannequin::PlayE_Skill(const FInputActionValue& value)
{
	Super::PlayE_Skill(value);

	if (GetCurHp() <= 0) return;

	bool isPressed = value.Get<bool>();

	if (_invenCom->_currentWeapon == nullptr) return;

	if (isPressed && _animInstanceTM != nullptr && _invenCom->_currentWeapon->_Itemid == 3)
	{
		if (auto _animInstTM = Cast<UTFT_AnimInstance_TestMannequin>(_animInstanceTM))
		{
			_animInstTM->PlayE_SkillMontage();

			
			UIMANAGER->GetSkillUI()->RunCDT(1);
		}
	}
}

void ATFT_TestMannequin::PlayQ_Skill(const FInputActionValue& value)
{
	Super::PlayQ_Skill(value);

	if (GetCurHp() <= 0) return;

	bool isPressed = value.Get<bool>();

	if (_invenCom->_currentWeapon == nullptr) return;

	if (isPressed && _animInstanceTM != nullptr && _invenCom->_currentWeapon->_Itemid == 1)
	{
		if (auto _animInstTM = Cast<UTFT_AnimInstance_TestMannequin>(_animInstanceTM))
		{
			_animInstTM->PlayQ_SkillMontage();

			
			UIMANAGER->GetSkillUI()->RunCDT(0);
		}
	}
}

void ATFT_TestMannequin::PlayAttack(const FInputActionValue& value)
{
	Super::PlayAttack(value);

	if (GetCurHp() <= 0) return;
	if (_invenCom->_currentWeapon == nullptr) return;

	bool isPressed = value.Get<bool>();

	if (_isAttacking == false && isPressed && _animInstanceTM != nullptr)
	{
		if (auto _animInstTM = Cast<UTFT_AnimInstance_TestMannequin>(_animInstanceTM))
		{
			if (_invenCom->_currentWeapon->_Itemid == 1)
			{
				_animInstTM->PlayAttackMontage();
				_isAttacking = true;

				_curAttackIndex %= 3;
				_curAttackIndex++;

				_animInstTM->JumpToSection(_curAttackIndex);
			}
			else if (_invenCom->_currentWeapon->_Itemid == 3)
			{
				_animInstTM->PlayAttackMontage2Hend();
				_isAttacking = true;

				_curAttackIndex %= 2;
				_curAttackIndex++;

				_animInstTM->JumpToSection(_curAttackIndex);
			}
			else
			{
				//UE_LOG(LogTemp, Log, TEXT("no Weapon no attack"));
				_animInstTM->PlayAttackMontage();
			}
		}
	}
}

void ATFT_TestMannequin::Dash(const FInputActionValue& value)
{
	Super::Dash(value);

	if (GetCurHp() <= 0) return;

	if (bCanDash && GetVelocity() != FVector::ZeroVector && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		FVector _dir = GetLastMovementInputVector().GetSafeNormal();

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TestMannequin::SetBlockInputOnDash_False, 0.5f, false);

		LaunchCharacter((_dir * dashStrength_Ground), false, false);
		bCanDash = false;
	}
}

void ATFT_TestMannequin::DoubleTapDash_Front(const FInputActionValue& value)
{
	Super::DoubleTapDash_Front(value);

	if (GetCurHp() <= 0) return;

	if (bCanDash && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		bCanDash = false;

		FVector from = GetActorLocation();
		FVector to = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		to.Z = from.Z;

		FVector _dir = UKismetMathLibrary::GetDirectionUnitVector(from, to).RotateAngleAxis(180.0f, FVector(0, 0, 1));

		LaunchCharacter((_dir * dashStrength_Ground), false, false);

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TestMannequin::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TestMannequin::DoubleTapDash_Back(const FInputActionValue& value)
{
	Super::DoubleTapDash_Back(value);

	if (GetCurHp() <= 0) return;

	if (bCanDash && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		bCanDash = false;

		FVector from = GetActorLocation();
		FVector to = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		to.Z = from.Z;

		FVector _dir = UKismetMathLibrary::GetDirectionUnitVector(from, to);

		LaunchCharacter((_dir * dashStrength_Ground), false, false);

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TestMannequin::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TestMannequin::DoubleTapDash_Left(const FInputActionValue& value)
{
	Super::DoubleTapDash_Left(value);

	if (GetCurHp() <= 0) return;

	if (bCanDash && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		bCanDash = false;

		FVector from = GetActorLocation();
		FVector to = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		to.Z = from.Z;

		FVector _dir = UKismetMathLibrary::GetDirectionUnitVector(from, to).RotateAngleAxis(90.0f, FVector(0, 0, 1));

		LaunchCharacter((_dir * dashStrength_Ground), false, false);

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TestMannequin::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TestMannequin::DoubleTapDash_Right(const FInputActionValue& value)
{
	Super::DoubleTapDash_Right(value);

	if (GetCurHp() <= 0) return;

	if (bCanDash && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		bCanDash = false;

		FVector from = GetActorLocation();
		FVector to = GetWorld()->GetFirstPlayerController()->GetPawn()->FindComponentByClass<UCameraComponent>()->GetComponentLocation();
		to.Z = from.Z;

		FVector _dir = UKismetMathLibrary::GetDirectionUnitVector(from, to).RotateAngleAxis(270.0f, FVector(0, 0, 1));

		LaunchCharacter((_dir * dashStrength_Ground), false, false);

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TestMannequin::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TestMannequin::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;


	if (_animInstanceTM)
	{
		_animInstanceTM->PlaySprintMontage();
	}
}

void ATFT_TestMannequin::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;


	if (_animInstanceTM)
	{
		_animInstanceTM->StopSprintMontage();
	}
}

void ATFT_TestMannequin::DashEnd()
{
	if (!bCanDash)
	{
		bCanDash = true;
		bBlockInputOnDash = false;

		GetCharacterMovement()->StopMovementImmediately();

		isDashing = false;
	}
}

void ATFT_TestMannequin::AttackStart()
{
	Super::AttackStart();

	if (_invenCom->_currentWeapon->_Itemid == 1)
	{
		SoundManager->Play("Knight_Swing", GetActorLocation());
	}
	else if (_invenCom->_currentWeapon->_Itemid == 3)
	{
		SoundManager->Play("Hammer_Swing", GetActorLocation());
	}
}

void ATFT_TestMannequin::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 100.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel9,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;

		hitResult.GetActor()->TakeDamage(50.0f, damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;
	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 20, drawColor, false, 2.0f);
}

void ATFT_TestMannequin::AttackHit_Q()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 100.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel9,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;
	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		
		hitResult.GetActor()->TakeDamage(300.0f, damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;
	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 20, drawColor, false, 2.0f);
}

void ATFT_TestMannequin::FootStep()
{
	Super::FootStep();

	auto player = GetWorld()->GetFirstPlayerController()->GetOwner();

	FVector start = GetActorLocation();
	FRotator rotator = GetActorRotation();
	FVector lineDirAndDist = FVector(1.0f, 1.0f, -100.0f);
	FVector end = start * lineDirAndDist;
	FHitResult hitResult;

	FCollisionQueryParams qParams;
	qParams.AddIgnoredActor(this);
	qParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel
	(
		hitResult,
		start,
		end,
		ECollisionChannel::ECC_Visibility,
		qParams
	);

	if (hitResult.PhysMaterial != nullptr)
	{

		FString hitName = hitResult.PhysMaterial->GetName();

		UE_LOG(LogTemp, Log, TEXT("%s"), *hitName);
	}

	if (hitResult.PhysMaterial != nullptr)
	{
		switch (hitResult.PhysMaterial->SurfaceType)
		{
		case SurfaceType1:
			SoundManager->Play("Knight_Walk_Stone", end);
			break;
		case SurfaceType2:
			SoundManager->Play("Knight_Walk_Grass", end);
			break;
		case SurfaceType3:
			SoundManager->Play("Knight_Walk_Water", end);
			break;
		default:
			break;
		}
	}
}