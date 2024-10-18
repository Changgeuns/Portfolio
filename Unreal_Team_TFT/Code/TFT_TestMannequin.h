// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_TestMannequin.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TestMannequin : public ATFT_Player
{
	GENERATED_BODY()
	
public:
	ATFT_TestMannequin();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void PlayE_Skill(const FInputActionValue& value) override;
	virtual void PlayQ_Skill(const FInputActionValue& value) override;
	virtual void PlayAttack(const FInputActionValue& value) override;

	virtual void Dash(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Front(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Back(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Left(const FInputActionValue& value) override;
	virtual void DoubleTapDash_Right(const FInputActionValue& value) override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;

	void DashEnd();

	void SetBlockInputOnDash_False() { bBlockInputOnDash = false; }

	virtual void AttackStart() override;

	UFUNCTION()
	void AttackHit();

	UFUNCTION()
	void AttackHit_Q();

	virtual void FootStep() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 600.0f;

};
