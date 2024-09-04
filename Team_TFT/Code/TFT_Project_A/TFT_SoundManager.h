// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFT_SoundManager.generated.h"

UCLASS()
class TFT_PROJECT_A_API ATFT_SoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATFT_SoundManager();

protected:
	void CreateSoundCue(FString keyName, FString path);

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void Play(FString keyName, FVector playLocation, FRotator playRotator = FRotator::ZeroRotator);

private:
	int32 _poolCount = 5;
	TMap<FString, class USoundCue*> _table;

};
