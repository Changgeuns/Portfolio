// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Knight.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "TFT_MeshComponent.h"

#include "TFT_SoundManager.h"
#include "TFT_Effect_Manager.h"
#include "TFT_GameInstance.h"

#include "TFT_HpBar.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

ATFT_Knight::ATFT_Knight()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));
	
	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonTerra/Characters/Heroes/Terra/Meshes/Terra.Terra'");

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

void ATFT_Knight::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceKnight = Cast<UTFT_AnimInstance_Knight>(GetMesh()->GetAnimInstance());
	if (_animInstanceKnight->IsValidLowLevel())
	{
		_animInstanceKnight->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
		_animInstanceKnight->_attackStartDelegate.AddUObject(this, &ATFT_Knight::AttackStart);
		_animInstanceKnight->_attackHitDelegate.AddUObject(this, &ATFT_Knight::AttackHit);
		_animInstanceKnight->_deathStartDelegate.AddUObject(this, &ATFT_Knight::DeathStart);
		_animInstanceKnight->_deathEndDelegate.AddUObject(this, &ATFT_Knight::Disable);

		_animInstanceKnight->_footStepDelegate.AddUObject(this, &ATFT_Knight::FootStep);
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

	UE_LOG(LogTemp, Warning, TEXT("Knight... hp : %d, attackDamage : %d"), _statCom->GetMaxHp(), _statCom->GetAttackDamage());

}

void ATFT_Knight::BeginPlay()
{
	Super::BeginPlay();

	_statCom->SetLevelAndInit(8);
}

void ATFT_Knight::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_Knight::AttackStart()
{
	Super::AttackStart();

	SoundManager->Play("Knight_Swing", GetActorLocation());
}

void ATFT_Knight::AttackHit()
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
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), damageEvent, GetController(), this);
		_hitPoint = hitResult.ImpactPoint;
		EffectManager->Play("N_Knight_Attack_Hit", 1, _hitPoint);
	}
}

void ATFT_Knight::DeathStart()
{
	Super::DeathStart();

	SoundManager->Play("Knight_Death", GetActorLocation());

	_animInstanceKnight->_deathStartDelegate.RemoveAll(this);
}

void ATFT_Knight::Disable()
{
	Super::Disable();

	_animInstanceKnight->_deathEndDelegate.RemoveAll(this);
}

void ATFT_Knight::FootStep()
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
