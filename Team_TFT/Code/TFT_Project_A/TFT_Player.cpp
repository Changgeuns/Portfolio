// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Player.h"
#include "TFT_Creature.h"
#include "TFT_Knight.h"
#include "Components/CapsuleComponent.h"


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "TFT_GameInstance.h"
#include "TFT_UIManager.h"
#include "TFT_Effect_Manager.h"
#include "TFT_InvenUI.h"
#include "TFT_Item.h"
#include "TFT_Effect_Manager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"

ATFT_Player::ATFT_Player()
{
	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_springArm->SetupAttachment(GetCapsuleComponent());
	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_springArm);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	_statCom->SetExp(0);

}

void ATFT_Player::BeginPlay()
{
	Super::BeginPlay();

	_invenCom->_itemAddedEvent.AddUObject(this, &ATFT_Player::AddItemHendle);
	_invenCom->_GoldChangeEvnet.AddUObject(this, &ATFT_Player::UIGold);
	UIMANAGER->GetInvenUI()->_SlotItemEvent.AddUObject(this, &ATFT_Player::DropItemPlayer);
}

void ATFT_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATFT_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATFT_Player::Init()
{

}

void ATFT_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &ATFT_Player::Move);

	
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &ATFT_Player::Look);

	
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &ATFT_Player::JumpA);

	
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &ATFT_Player::AttackA);

	
		EnhancedInputComponent->BindAction(_invenOpenAction, ETriggerEvent::Started, this, &ATFT_Player::InvenopenA);


		EnhancedInputComponent->BindAction(_skillAction, ETriggerEvent::Started, this, &ATFT_Player::UseSkill);
	}
}

void ATFT_Player::Interact(ATFT_Item* item)
{
	UE_LOG(LogTemp, Log, TEXT("Player Interact With NPC!"));

	AddItemPlayer(item);
}

void ATFT_Player::LevelUp()
{
	EffectManager->Play("N_Player_LevelUp", 1, GetActorLocation());
}

void ATFT_Player::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		_vertical = MovementVector.Y;
		_horizontal = MovementVector.X;

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ATFT_Player::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void ATFT_Player::JumpA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		ACharacter::Jump();
	}
}


void ATFT_Player::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	auto player = Cast<ATFT_Knight>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (isPressed && !_isAttacking && _animInstanceKnight != nullptr && player != nullptr)
	{
		if (auto knightAnimInstance = Cast<UTFT_AnimInstance_Knight>(_animInstanceKnight))
		{
			knightAnimInstance->PlayAttackMontage();
			_isAttacking = true;

			_curAttackIndex %= 3;
			_curAttackIndex++;

			knightAnimInstance->JumpToSection(_curAttackIndex);
		}

		return;
	}

	if (isPressed && !_isAttacking && _animInstanceArcher != nullptr)
	{
		if (auto archerAnimInstance = Cast<UTFT_AnimInstance_Archer>(_animInstanceArcher))
		{
			archerAnimInstance->PlayAttackMontage();
			_isAttacking = true;

			_curAttackIndex %= 3;
			_curAttackIndex++;

			archerAnimInstance->JumpToSection(_curAttackIndex);
		}

		return;
	}

}

void ATFT_Player::InvenopenA(const FInputActionValue& value)
{
	UIMANAGER->GetInvenUI()->UIGold(_invenCom->GetPlayerGold());


	UIMANAGER->_invenOpenEvent.Broadcast();
}

void ATFT_Player::UseSkill(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		UE_LOG(LogTemp, Warning, TEXT("Skill activated"));

		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f; 
		FRotator SpawnRotation = GetActorRotation(); 
		EffectManager->Play(TEXT("Fireball"), 1, SpawnLocation, SpawnRotation);

		UE_LOG(LogTemp, Warning, TEXT("Effect should be visible at location: %s"), *SpawnLocation.ToString());
	}
}

void ATFT_Player::AddItemPlayer(ATFT_Item* item) 
{
	_invenCom->AddItem(item);

	_statCom->AddAttackDamage(item->GetItemAttackDamage());
}

void ATFT_Player::AddItemHendle(ATFT_Item* item, int32 index) 
{
	UIMANAGER->GetInvenUI()->AddUiItem(item, index);
}

void ATFT_Player::DropItemPlayer(ATFT_Item* item, int32 index)
{
	_invenCom->DropItem(index);

	_statCom->AddAttackDamage(-item->GetItemAttackDamage());
}

void ATFT_Player::UIGold(int32 gold)
{
	UIMANAGER->GetInvenUI()->UIGold(gold);
}
