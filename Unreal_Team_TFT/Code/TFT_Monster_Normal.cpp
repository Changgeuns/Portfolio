// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Monster_Normal.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

#include "TFT_HpBar.h"
#include "TFT_AnimInstance_Monster.h"

#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"

#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"
#include "TFT_Monster_AIController.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

ATFT_Monster_Normal::ATFT_Monster_Normal()
{
	PrimaryActorTick.bCanEverTick = true;

	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	_invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'");

	_hpbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));

	_hpbarWidget->SetupAttachment(GetMesh());
	_hpbarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpbarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 300.0f));


	static ConstructorHelpers::FClassFinder<UUserWidget> hpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_HpBar_Nomal_BP.TFT_HpBar_Nomal_BP_C'"));
	if (hpBar.Succeeded())
	{
		_hpbarWidget->SetWidgetClass(hpBar.Class);
	}

	_possessionExp = 10;


}

void ATFT_Monster_Normal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance_Normal = Cast<UTFT_AnimInstance_Monster>(GetMesh()->GetAnimInstance());

	if (_animInstance_Normal->IsValidLowLevel())
	{
		_animInstance_Normal->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
		_animInstance_Normal->_attackStartDelegate.AddUObject(this, &ATFT_Monster_Normal::AttackStart);
		_animInstance_Normal->_attackHitDelegate.AddUObject(this, &ATFT_Monster_Normal::AttackHit);
		_animInstance_Normal->_deathStartDelegate.AddUObject(this, &ATFT_Monster_Normal::DeathStart);
		_animInstance_Normal->_deathEndDelegate.AddUObject(this, &ATFT_Monster_Normal::Disable);
	}


	_hpbarWidget->InitWidget();
	auto hpBar = Cast<UTFT_HpBar>(_hpbarWidget->GetUserWidgetObject());

	if (hpBar)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UTFT_HpBar::SetHpBarValue);
	}
}

void ATFT_Monster_Normal::BeginPlay()
{
	Super::BeginPlay();

	_statCom->SetLevelAndInit(100);

	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceWeight = 1.0f;
}

void ATFT_Monster_Normal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (Player)
	{	
		float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());	
		if (_hpbarWidget)
		{	
			if (Distance <= 600.0f) 
			{
				_hpbarWidget->SetVisibility(true);
				_hpbarWidget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				_hpbarWidget->SetVisibility(false);
				_hpbarWidget->GetUserWidgetObject()->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
	
	// MaintainDistanceFromOtherAIs();
}

void ATFT_Monster_Normal::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_Monster_Normal::Attack_AI()
{
	Super::Attack_AI();

	if (_isAttacking == false && _animInstance_Normal != nullptr)
	{
		_animInstance_Normal->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance_Normal->JumpToSection(_curAttackIndex);
	}
}

void ATFT_Monster_Normal::AttackStart()
{
	Super::AttackStart();

	SoundManager->Play("Monster_Normal_Swing", GetActorLocation());
}

void ATFT_Monster_Normal::AttackHit()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 600.0f;
	float attackRadius = 100.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel10,
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
	}
}

void ATFT_Monster_Normal::MaintainDistanceFromOtherAIs()
{
	TArray<AActor*> OtherAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFT_Monster_Normal::StaticClass(), OtherAIs);

	for (AActor* Actor : OtherAIs)
	{
		ATFT_Monster_Normal* OtherAI = Cast<ATFT_Monster_Normal>(Actor);

		if (OtherAI && OtherAI != this)
		{
			FVector TargetLocation = GetActorLocation();
			float Distance = FVector::Dist(TargetLocation, OtherAI->GetActorLocation());

			if (Distance < 200.0f)  
			{
				FVector AvoidDirection = (TargetLocation - OtherAI->GetActorLocation()).GetSafeNormal();
				TargetLocation += AvoidDirection * FMath::RandRange(50.0f, 100.0f);  

				AAIController* AIController = Cast<AAIController>(GetController());
				if (AIController)
				{
					AIController->MoveToLocation(TargetLocation);
				}
			}
		}
	}
}

void ATFT_Monster_Normal::DropItem()
{
	Super::DropItem();
}

void ATFT_Monster_Normal::DeathStart()
{
	Super::DeathStart();

	SoundManager->Play("Monster_Normal_Death", GetActorLocation());

	_animInstance_Normal->_deathStartDelegate.RemoveAll(this);
}

void ATFT_Monster_Normal::Disable()
{
	Super::Disable();

	_animInstance_Normal->_deathEndDelegate.RemoveAll(this);
}
