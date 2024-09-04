// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Archer.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

#include "TFT_SoundManager.h"
#include "TFT_Effect_Manager.h"
#include "TFT_GameInstance.h"

#include "TFT_Projectile.h"

#include "TFT_HpBar.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Blueprint/UserWidget.h"

ATFT_Archer::ATFT_Archer()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));
	
	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'");

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

	static ConstructorHelpers::FClassFinder<ATFT_Projectile> projectile
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Objects/TFT_Projectile_BP.TFT_Projectile_BP_C'"));
	if (projectile.Succeeded())
	{
		_projectileClass = projectile.Class;
	}
}

void ATFT_Archer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstanceArcher = Cast<UTFT_AnimInstance_Archer>(GetMesh()->GetAnimInstance());
	if (_animInstanceArcher->IsValidLowLevel())
	{
		_animInstanceArcher->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
		_animInstanceArcher->_attackStartDelegate.AddUObject(this, &ATFT_Archer::AttackStart);
		_animInstanceArcher->_attackHitDelegate.AddUObject(this, &ATFT_Archer::AttackHit_ADC);
		_animInstanceArcher->_deathStartDelegate.AddUObject(this, &ATFT_Archer::DeathStart);
		_animInstanceArcher->_deathEndDelegate.AddUObject(this, &ATFT_Archer::Disable);
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


	UE_LOG(LogTemp, Warning, TEXT("Archer... hp : %d, attackDamage : %d"), _statCom->GetMaxHp(), _statCom->GetAttackDamage());
}

void ATFT_Archer::BeginPlay()
{
	Super::BeginPlay();

	_statCom->SetLevelAndInit(1);
}

void ATFT_Archer::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_Archer::AttackStart()
{
	Super::AttackStart();

	SoundManager->Play("Archer_Shoot", GetActorLocation());
}

void ATFT_Archer::AttackHit_ADC()
{
	if (_projectileClass)
	{
		FVector forward = GetActorForwardVector();
		FVector fireLocation = GetActorLocation() + forward * 150;

		auto projectile = GetWorld()->SpawnActor<ATFT_Projectile>(_projectileClass, fireLocation, FRotator::ZeroRotator);
		projectile->FireInDirection(forward);
	}

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
		_hitPoint = hitResult.ImpactPoint;

		EffectManager->Play("N_Archer_Attack_Hit", 1, _hitPoint);
	}

	
}

void ATFT_Archer::DeathStart()
{
	Super::DeathStart();

	SoundManager->Play("Archer_Death", GetActorLocation());

	_animInstanceArcher->_deathStartDelegate.RemoveAll(this);
}

void ATFT_Archer::Disable()
{
	Super::Disable();

	_animInstanceArcher->_deathEndDelegate.RemoveAll(this);
}
