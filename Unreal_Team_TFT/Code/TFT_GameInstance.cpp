// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_GameInstance.h"

#include "TFT_UIManager.h"
#include "TFT_Effect_Manager.h"
#include "TFT_SoundManager.h"

UTFT_GameInstance::UTFT_GameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable
	(TEXT("/Script/Engine.DataTable'/Game/Data/TFT_StatDataTable.TFT_StatDataTable'"));

	if (dataTable.Succeeded())
	{
		_statTable = dataTable.Object;
		UE_LOG(LogTemp, Error, TEXT("StatTable Load Complete"));
	}
}

void UTFT_GameInstance::Init()
{
	Super::Init();

	auto statData = GetStatDataByLevel(10);

	UE_LOG(LogTemp, Warning, TEXT("Level : %d , MaxHp : %d , MaxHp : %d , Attack : %d")
		, statData->level, statData->maxHP, statData->maxMP, statData->attack);

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_uiManager = GetWorld()->SpawnActor<ATFT_UIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	params.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<ATFT_Effect_Manager>(FVector::ZeroVector, FRotator::ZeroRotator, params);
	
	params.Name = TEXT("SoundManager");
	_soundManager = GetWorld()->SpawnActor<ATFT_SoundManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);
}

FTFT_StatData* UTFT_GameInstance::GetStatDataByLevel(int32 level)
{
	auto statData = _statTable->FindRow<FTFT_StatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}
