// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TM_DH.h"

#include "TFT_MeshComponent.h"
#include "TFT_Effect_Manager.h"
#include "TFT_GameInstance.h"
#include "TFT_Monster.h"
#include "Engine/DamageEvents.h"

#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"


ATFT_TM_DH::ATFT_TM_DH()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/BluePrint/Player/Mesh/SKM_Manny_Simple_DH.SKM_Manny_Simple_DH'");

	
	FName WeaponSocket(TEXT("WeaponSocket")); 
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

		
		static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponAsset(TEXT("/Script/Engine.StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_GreatAxe.SM_GreatAxe'"));
		if (WeaponAsset.Succeeded())
		{
			Weapon->SetStaticMesh(WeaponAsset.Object);  
		}

		
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ATFT_TM_DH::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	_animInstanceDH = Cast<UTFT_AnimInstance_DH>(GetMesh()->GetAnimInstance());

	
	
	if (_animInstanceDH != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimInstance_DH initialized successfully."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AnimInstance_DH is null."));
	}
}

void ATFT_TM_DH::BeginPlay()
{
	Super::BeginPlay();
}

void ATFT_TM_DH::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_TM_DH::PlayE_Skill(const FInputActionValue& value)
{
	Super::PlayE_Skill(value);

	bool isPressed = value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("PlayE_Skill called, isPressed: %d"), isPressed);

	if (isPressed && _animInstanceDH != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling PlayE_SkillMontage..."));
		_animInstanceDH->PlayE_SkillMontage();


	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("_animInstanceDH is null or isPressed is false"));
	}
}

void ATFT_TM_DH::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

	
	if (_animInstanceDH)
	{
		_animInstanceDH->PlaySprintMontage();  
	}
}

void ATFT_TM_DH::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;  

	
	if (_animInstanceDH)
	{
		_animInstanceDH->StopSprintMontage();  
	}
}
