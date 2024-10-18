// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_TM_CG.generated.h"

/**
 * 
 */
UCLASS()
class TFT_PROJECT_A_API ATFT_TM_CG : public ATFT_Player
{
	GENERATED_BODY()
public:
	ATFT_TM_CG();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;


	void AttackA(const FInputActionValue& value) override;
private:

};
