// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Creature.h"

#include "TFT_GameInstance.h"
#include "TFT_InvenComponent.h"

#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Math/UnrealMathUtility.h"
#include "TFT_Item.h"
#include "TFT_StatComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "TFT_HpBar.h"
#include "TFT_PlayerController.h"
#include "Components/Button.h"


ATFT_Creature::ATFT_Creature()
{

	PrimaryActorTick.bCanEverTick = true;

	_statCom = CreateDefaultSubobject<UTFT_StatComponent>(TEXT("Stat_Com"));

}


void ATFT_Creature::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFT_Creature::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



void ATFT_Creature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_Creature::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttacking = false;
	_attackEndedDelegate.Broadcast();
}


void ATFT_Creature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATFT_Creature::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = -(_statCom->AddCurHp(-Damage));

	return damaged;
}

void ATFT_Creature::AttackStart()
{
}

void ATFT_Creature::DeathStart()
{
	this->SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if (controller != nullptr) GetController()->UnPossess();
}

void ATFT_Creature::Disable()
{
	this->SetActorHiddenInGame(true);
}
