// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_TM_BJ.generated.h"

UCLASS()
class TFT_PROJECT_A_API ATFT_TM_BJ : public ATFT_Player
{
	GENERATED_BODY()
public:
	ATFT_TM_BJ();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void PlayAttack(const FInputActionValue& value) override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttcking = false;
};
