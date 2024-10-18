// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_TM_IY.generated.h"

UCLASS()
class TFT_PROJECT_A_API ATFT_TM_IY : public ATFT_Player
{
	GENERATED_BODY()
public:
	ATFT_TM_IY();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void Dash(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Front(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Back(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Left(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Right(const FInputActionValue& value) override;

	void DashEnd();

	void SetBlockInputOnDash_False() { bBlockInputOnDash = false; }

	virtual void PlayQ_Skill(const FInputActionValue& value) override;

	UFUNCTION()
	void AttackHit();

	virtual void InitState() override;

private:

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill, meta = (AloowPrivateAccess = true))
	bool bSkillBool_1 = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill, meta = (AloowPrivateAccess = true))
	bool bSkillBool_2 = true;

	
};
