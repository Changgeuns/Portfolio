// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Effect_Manager.h"

#include "Components/SceneComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TFT_Effect.h"

ATFT_Effect_Manager::ATFT_Effect_Manager()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	_rootComponent = CreateDefaultSubobject<USceneComponent>("RootCom");
	RootComponent = _rootComponent;

	CreateParticleClass(TEXT("P_Explosion"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_Effect_BP.TFT_Effect_BP_C'"));
	CreateParticleClass(TEXT("N_Knight_Attack_Hit"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_N_Knight_Attack_Hit_BP.TFT_N_Knight_Attack_Hit_BP_C'"));
	CreateParticleClass(TEXT("N_Archer_Attack_Hit"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_N_Archer_Attack_Hit_BP.TFT_N_Archer_Attack_Hit_BP_C'"));
	CreateParticleClass(TEXT("N_Monster_Boss_Attack_Hit"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_N_Monster_Boss_Attack_Hit_Effect_BP.TFT_N_Monster_Boss_Attack_Hit_Effect_BP_C'"));
	CreateParticleClass(TEXT("Fireball"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_Skill_BP.TFT_Skill_BP_C'"));
	CreateParticleClass(TEXT("N_Player_LevelUp"), TEXT("/Script/Engine.Blueprint'/Game/BluePrint/VFX/TFT_N_Player_LevelUp_BP.TFT_N_Player_LevelUp_BP_C'"));
}

void ATFT_Effect_Manager::CreateParticleClass(FString name, FString path)
{
	if (_classTable.Contains(name) == true)
	{
		UE_LOG(LogTemp, Error, TEXT("%s already exist in classTable"), *name);
		return;
	}

	ConstructorHelpers::FClassFinder<ATFT_Effect> effect(*path);
	if (effect.Succeeded())
	{
		_classTable.Add(name);
		_classTable[name] = effect.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("cant find : %s"), *path);
		return;
	}
}


void ATFT_Effect_Manager::BeginPlay()
{
	Super::BeginPlay();
	CreateEffect();
}

void ATFT_Effect_Manager::CreateEffect()
{
	for (auto classPair : _classTable)
	{
		FString name = classPair.Key;

		_effectTable.Add(name);
		for (int32 i = 0; i < _poolCount; i++)
		{
			FString tempName = name + FString::FromInt(i);
			FActorSpawnParameters params;
			params.Name = FName(*tempName);
			auto effect = GetWorld()->SpawnActor<ATFT_Effect>(classPair.Value, FVector::ZeroVector, FRotator::ZeroRotator, params);

			effect->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			_effectTable[name].Add(effect);
		}
	}
}


void ATFT_Effect_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_Effect_Manager::Play(FString name, int32 effectType, FVector location, FRotator rotator)
{
	if (_effectTable.Contains(name) == false)
		return;

	auto findEffect = _effectTable[name].FindByPredicate(
		[](ATFT_Effect* effect)-> bool
		{
			if (effect->IsPlaying())
				return false;
			return true;
		});

	if (findEffect)
		(*findEffect)->Play(effectType, location, rotator);
}

