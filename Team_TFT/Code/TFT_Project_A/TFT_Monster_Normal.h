// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TFT_Monster.h"
#include "TFT_Monster_Normal.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_Monster_Normal : public ATFT_Monster
{
	GENERATED_BODY()

public:
	ATFT_Monster_Normal();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void Attack_AI() override;

	virtual void AttackStart() override;

	UFUNCTION()
	void AttackHit();

	

	virtual void DropItem() override;
	
	virtual void DeathStart() override;

	virtual void Disable() override;

protected:


private:

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = true))
	class UTFT_AnimInstance_Monster* _animInstance_Normal;
	
};
