// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_Knight.generated.h"



UCLASS()
class TFT_PROJECT_A_API ATFT_Knight : public ATFT_Player
{
	GENERATED_BODY()

public:
	ATFT_Knight();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	virtual void SetMesh(FString path) override;

	virtual void AttackStart() override;

	UFUNCTION()
	void AttackHit();

	virtual void DeathStart() override;

	virtual void Disable() override;
	
public:

private:


};
