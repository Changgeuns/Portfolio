// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Player.h"
#include "TFT_Creature.h"
#include "TFT_Knight.h"
#include "TFT_Monster.h"
#include "TFT_TeamAI.h"
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
#include "TFT_Equipment_Window.h"
#include "TFT_SoundManager.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"
#include "Engine/DamageEvents.h"

#include "TFT_TM_SkillUI.h"
#include "UTFT_PartyHPWidget.h"

#include "Components/BoxComponent.h"
#include "Engine/OverlapResult.h"

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

	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	_triggerBox->SetupAttachment(RootComponent);
	_triggerBox->SetBoxExtent(FVector(300.f, 300.f, 100.f));
	_triggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void ATFT_Player::BeginPlay()
{
	Super::BeginPlay();

	if (_invenCom != nullptr)
	{
		_invenCom->_itemAddedEvent.AddUObject(this, &ATFT_Player::AddItemHendle);
		_invenCom->_GoldChangeEvnet.AddUObject(this, &ATFT_Player::UIGold);
		UIMANAGER->_EquipmentCloseResetEvent.AddUObject(this, &ATFT_Player::CloseResetEquipment);
		UIMANAGER->GetInvenUI()->_SlotItemEvent.AddUObject(this, &ATFT_Player::DropItemPlayer);
		UIMANAGER->GetInvenUI()->_itemSellEvent.AddUObject(this, &ATFT_Player::SellItemPlayer);
		UIMANAGER->GetInvenUI()->_itemUesEvent.AddUObject(this, &ATFT_Player::UseItemPlayer);
		UIMANAGER->GetEquipmentUI()->_ItemChangeEvent.AddUObject(this, &ATFT_Player::ChangeEquipment);
		UIMANAGER->GetEquipmentUI()->_ItemChangeEvent_stat.AddUObject(this, &ATFT_Player::UseItemPlayer_Equipment);
	}

	if (_triggerBox != nullptr)
	{
		_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATFT_Player::OnOverlapBegin);
		_triggerBox->OnComponentEndOverlap.AddDynamic(this, &ATFT_Player::OnOverlapEnd);
	}
}

void ATFT_Player::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATFT_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// SetPartyUI();
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
	
		EnhancedInputComponent->BindAction(_dashAction, ETriggerEvent::Started, this, &ATFT_Player::Dash);

		EnhancedInputComponent->BindAction(_doubleTapDash_W_Action, ETriggerEvent::Triggered, this, &ATFT_Player::DoubleTapDash_Front);
		EnhancedInputComponent->BindAction(_doubleTapDash_A_Action, ETriggerEvent::Triggered, this, &ATFT_Player::DoubleTapDash_Left);
		EnhancedInputComponent->BindAction(_doubleTapDash_S_Action, ETriggerEvent::Triggered, this, &ATFT_Player::DoubleTapDash_Back);
		EnhancedInputComponent->BindAction(_doubleTapDash_D_Action, ETriggerEvent::Triggered, this, &ATFT_Player::DoubleTapDash_Right);

		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &ATFT_Player::AttackA);

		EnhancedInputComponent->BindAction(_invenOpenAction, ETriggerEvent::Started, this, &ATFT_Player::InvenopenA);

		EnhancedInputComponent->BindAction(_EquipmentAction, ETriggerEvent::Started, this, &ATFT_Player::EquipmentA);

		EnhancedInputComponent->BindAction(_skillAction, ETriggerEvent::Started, this, &ATFT_Player::UseSkill);

		EnhancedInputComponent->BindAction(_playESkillAction, ETriggerEvent::Started, this, &ATFT_Player::PlayE_Skill);

		EnhancedInputComponent->BindAction(_playQSkillAction, ETriggerEvent::Started, this, &ATFT_Player::PlayQ_Skill);

		EnhancedInputComponent->BindAction(_playAttackAction, ETriggerEvent::Started, this, &ATFT_Player::PlayAttack);

		EnhancedInputComponent->BindAction(_rollingAction, ETriggerEvent::Started, this, &ATFT_Player::Rolling);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ATFT_Player::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATFT_Player::StopSprint);
	}
}

void ATFT_Player::Interact(ATFT_Item* item)
{
	

	if (_invenCom != nullptr && _invenCom->GetPlayerGold() > item->GetItemGold())
	{
		UE_LOG(LogTemp, Log, TEXT("Item Buy Succsess"));
		_invenCom->AddPlayerGold(-item->GetItemGold());
		AddItemPlayer(item);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("your gold is lacking "));
	}
}

void ATFT_Player::LevelUp()
{
	EffectManager->Play("N_Player_LevelUp", 1, GetActorLocation());
}

void ATFT_Player::Move(const FInputActionValue& value)
{
	if (!_canMove) return;

	if (GetCurHp() <= 0) return;

	FVector2D MovementVector = value.Get<FVector2D>();

	if (bBlockInputOnDash) return;

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
	if (GetCurHp() <= 0) return;

	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void ATFT_Player::JumpA(const FInputActionValue& value)
{
	if (GetCurHp() <= 0) return;

	bool isPressed = value.Get<bool>();

	if (bBlockInputOnDash) return;

	if (isPressed)
	{
		ACharacter::Jump();
	}
}


void ATFT_Player::AttackA(const FInputActionValue& value)
{
	if (GetCurHp() <= 0) return;

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

	if (isPressed && !_isAttacking && _animInstanceBJ != nullptr)
	{
		if (auto testAnimInstance = Cast<UTFT_AnimInstance_BJ>(_animInstanceBJ))
		{
			testAnimInstance->PlayAttackMontage();
			_isAttacking = true;

			_curAttackIndex %= 3;
			_curAttackIndex++;

			testAnimInstance->JumpToSection(_curAttackIndex);
		}

		return;
	}

}

void ATFT_Player::InvenopenA(const FInputActionValue& value)
{
	UIMANAGER->GetInvenUI()->UIGold(_invenCom->GetPlayerGold());

	UIMANAGER->_invenOpenEvent.Broadcast();
}

void ATFT_Player::EquipmentA(const FInputActionValue& value)
{
	UIMANAGER->_EquipmentOpenEvent.Broadcast();
}

void ATFT_Player::UseSkill(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (SoundManager)
		{
			SoundManager->Play("Use_Skill", GetActorLocation());
		}

		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 300.0f;
		FRotator SpawnRotation = GetActorRotation();
		EffectManager->Play(TEXT("Fireball"), 1, SpawnLocation, SpawnRotation);
		
		FVector CollisionLocation = SpawnLocation; 
		float CollisionRadius = 200.0f; 
	
		UWorld* World = GetWorld();
		if (World)
		{
			FCollisionShape SkillCollision = FCollisionShape::MakeSphere(CollisionRadius);

			TArray<FHitResult> HitResults;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this); 
			bool bHit = World->SweepMultiByChannel(
				HitResults,
				CollisionLocation,
				CollisionLocation,
				FQuat::Identity,
				ECC_Pawn, 
				SkillCollision,
				Params
			);

			if (bHit)
			{
				for (FHitResult Hit : HitResults)
				{
					AActor* HitActor = Hit.GetActor();
					if (HitActor && HitActor->IsA(ATFT_Monster::StaticClass()))
					{
						
						float DamageAmount = 50.0f; 
						FDamageEvent DamageEvent;
						HitActor->TakeDamage(DamageAmount, DamageEvent, GetController(), this);

						UE_LOG(LogTemp, Warning, TEXT("Hit Monster: %s, Damage: %f"), *HitActor->GetName(), DamageAmount);
					}
				}
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Effect should be visible at location: %s"), *SpawnLocation.ToString());
	}
}

void ATFT_Player::Rolling()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(_rollingMontage);
}

void ATFT_Player::StartSprint()
{
}

void ATFT_Player::StopSprint()
{
}

void ATFT_Player::AddItemPlayer(ATFT_Item* item) 
{
	if(_invenCom != nullptr) _invenCom->AddItem(item);
}

void ATFT_Player::AddItemHendle(ATFT_Item* item, int32 index) 
{
	UIMANAGER->GetInvenUI()->AddUiItem(item, index);
}

void ATFT_Player::DropItemPlayer(ATFT_Item* item, int32 index)
{
	if (_invenCom != nullptr)  _invenCom->DropItem(index);
}

void ATFT_Player::SellItemPlayer(ATFT_Item* item, int32 index)
{
	if (_invenCom != nullptr)  _invenCom->SellItem(index);
}

void ATFT_Player::UseItemPlayer(ATFT_Item* item, int32 index)
{
	if (item->GetItemType() == "Equipment")
	{
		UE_LOG(LogTemp, Log, TEXT("Equipment Item Use"));

		UIMANAGER->GetEquipmentUI()->Set_Equipment(item);
		_invenCom->UseItem(index);
	}
	else if (item->GetItemType() == "Utility")
	{
		UE_LOG(LogTemp, Log, TEXT("Utility Item Use"));

		_invenCom->UseItem(index);
	}
}

void ATFT_Player::UseItemPlayer_Equipment(ATFT_Item* item)
{
	if (_statCom != nullptr) _statCom->AddAttackDamage(item->GetItemAttackDamage());
}

void ATFT_Player::UIGold(int32 gold)
{
	UIMANAGER->GetInvenUI()->UIGold(gold);
}

void ATFT_Player::ChangeEquipment(ATFT_Item* item)
{
	if (_statCom != nullptr) _statCom->AddAttackDamage(-item->GetItemAttackDamage());

	_invenCom->AddItem(item);

}

void ATFT_Player::CloseResetEquipment()
{
	UIMANAGER->GetEquipmentUI()->ResetChoice();
}

void ATFT_Player::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!_canMove) return;

	if (UIMANAGER->GetPartyHPUI()->IsOpened()) return;

	ATFT_TeamAI* teamAI = Cast<ATFT_TeamAI>(OtherActor);

	if (teamAI != nullptr)
	{
		UIMANAGER->OpenWidget(UIType::PartyHPUI);
	}
}

void ATFT_Player::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!_canMove) return;

	if (!UIMANAGER->GetPartyHPUI()->IsOpened()) return;

	ATFT_TeamAI* teamAI = Cast<ATFT_TeamAI>(OtherActor);

	if (teamAI != nullptr)
	{
		UIMANAGER->CloseWidget(UIType::PartyHPUI);
	}

	SetPartyUI();
}

void ATFT_Player::SetPartyUI()
{
	if (!_canMove) return;

	auto currentPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (currentPawn == nullptr) return;

	auto world = GetWorld();
	if (world == nullptr) return;

	FVector center = GetActorLocation();
	float searchRadius = 1500.0f;

	TArray<FOverlapResult> overlapResult;
	FCollisionQueryParams qParams(NAME_None, false, currentPawn);

	bool bResult = world->OverlapMultiByChannel
	(
		overlapResult,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(searchRadius),
		qParams
	);

	FColor drawColor = FColor::Green;

	if (bResult)
	{
		for (auto& result : overlapResult)
		{
			auto target = Cast<ATFT_TeamAI>(result.GetActor());

			if (target != nullptr)
			{
				drawColor = FColor::Red;

				if (UIMANAGER->GetPartyHPUI()->IsOpened()) return;

				UIMANAGER->OpenWidget(UIType::PartyHPUI);

				return;
			}
		}	
	}
	
	DrawDebugSphere(GetWorld(), center, searchRadius, 20, drawColor, false, 2.0f);

	if (!UIMANAGER->GetPartyHPUI()->IsOpened()) return;

	UIMANAGER->CloseWidget(UIType::PartyHPUI);
}
