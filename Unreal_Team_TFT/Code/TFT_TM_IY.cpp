// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TM_IY.h"

#include "TFT_MeshComponent.h"
#include "TFT_InvenComponent.h"

#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "TFT_GameInstance.h"
#include "TFT_UIManager.h"
#include "TFT_TM_SkillUI.h"

#include "Engine/DamageEvents.h"
#include "Components/SphereComponent.h"

ATFT_TM_IY::ATFT_TM_IY()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/BluePrint/Player/Mesh/SKM_Manny_Simple_IY.SKM_Manny_Simple_IY'");

	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));
}

void ATFT_TM_IY::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceIY = Cast<UTFT_AnimInstance_IY>(GetMesh()->GetAnimInstance());
	if (_animInstanceIY->IsValidLowLevel())
	{
		_animInstanceIY->_dashEndDelegate.AddUObject(this, &ATFT_TM_IY::DashEnd);
		_animInstanceIY->_attackHitDelegate.AddUObject(this, &ATFT_TM_IY::AttackHit);
		_animInstanceIY->_stunEndDelegate.AddUObject(this, &ATFT_TM_IY::InitState);
	}
}

void ATFT_TM_IY::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("%f"), GetCharacterMovement()->BrakingFrictionFactor);

	_statCom->SetLevelAndInit(10);
}

void ATFT_TM_IY::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TM_IY::Dash(const FInputActionValue& value)
{
	Super::Dash(value);

	
	
	if (bCanDash && GetVelocity() != FVector::ZeroVector && !GetCharacterMovement()->IsFalling())
	{
		isDashing = true;
		bBlockInputOnDash = true;
		FVector _dir = GetLastMovementInputVector().GetSafeNormal();

		FTimerHandle _timerHandle;
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TM_IY::SetBlockInputOnDash_False, 0.5f, false);

		LaunchCharacter((_dir * dashStrength_Ground), false, false);
		bCanDash = false;


		bCanDash = false;
	}	
}

void ATFT_TM_IY::DoubleTapDash_Front(const FInputActionValue& value)
{
	Super::DoubleTapDash_Front(value);



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
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TM_IY::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TM_IY::DoubleTapDash_Back(const FInputActionValue& value)
{
	Super::DoubleTapDash_Back(value);



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
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TM_IY::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TM_IY::DoubleTapDash_Left(const FInputActionValue& value)
{
	Super::DoubleTapDash_Left(value);



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
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TM_IY::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TM_IY::DoubleTapDash_Right(const FInputActionValue& value)
{
	Super::DoubleTapDash_Right(value);



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
		GetWorldTimerManager().SetTimer(_timerHandle, this, &ATFT_TM_IY::SetBlockInputOnDash_False, 0.5f, false);
	}
}

void ATFT_TM_IY::DashEnd()
{
	if (!bCanDash)
	{
		bCanDash = true;
		bBlockInputOnDash = false;

		GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
		
		GetCharacterMovement()->StopMovementImmediately();
		

		isDashing = false;
	}
}

void ATFT_TM_IY::PlayQ_Skill(const FInputActionValue& value)
{
	Super::PlayQ_Skill(value);

	bool isPressed = value.Get<bool>();

	if (isPressed && _animInstanceIY != nullptr)
	{
		if (auto _animInstIY = Cast<UTFT_AnimInstance_IY>(_animInstanceIY))
		{
			_animInstIY->PlayQ_SkillMontage();

			UIMANAGER->GetSkillUI()->SetSkillSlot(0, 5.0f, 1);
			UIMANAGER->GetSkillUI()->RunCDT(0);
		}

		return;
	}
}

void ATFT_TM_IY::AttackHit()
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
		
		hitResult.GetActor()->TakeDamage(1000.0f, damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;
	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 20, drawColor, false, 2.0f);
}

void ATFT_TM_IY::InitState()
{
	Super::InitState();
}
