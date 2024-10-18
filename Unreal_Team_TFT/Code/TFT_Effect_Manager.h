// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFT_Effect_Manager.generated.h"

class ATFT_Effect;

UCLASS()
class TFT_PROJECT_A_API ATFT_Effect_Manager : public AActor
{
	GENERATED_BODY()
	
public:	

	ATFT_Effect_Manager();

protected:
	void CreateParticleClass(FString name, FString path);


	virtual void BeginPlay() override;

	void CreateEffect();
public:	

	virtual void Tick(float DeltaTime) override;

	void Play(FString name, int32 effectType, FVector location, FRotator rotator = FRotator::ZeroRotator);

private:
	int32 _poolCount = 5;

	UPROPERTY()
	TMap<FString, TSubclassOf<ATFT_Effect>> _classTable;

	TMap<FString, TArray<ATFT_Effect*>> _effectTable;

	UPROPERTY()
	class USceneComponent* _rootComponent;
};
