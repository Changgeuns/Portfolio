// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_TM_DH.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TM_DH : public ATFT_Player
{
	GENERATED_BODY()
public:
	ATFT_TM_DH();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void PlayE_Skill(const FInputActionValue& value) override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	UStaticMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsSprinting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 600.0f;

	

};
