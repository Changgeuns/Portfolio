// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Creature.h"
#include "TFT_TeamAI.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TeamAI : public ATFT_Creature
{
	GENERATED_BODY()
	
public:
	ATFT_TeamAI();

	virtual void PostInitializeComponents() override;

	virtual void Init() PURE_VIRTUAL(ATFT_TeamAI::Init, );

	UFUNCTION()
	virtual void Attack_AI();

	virtual void AttackHit() PURE_VIRTUAL(ATFT_TeamAI::AttackHit, );

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = true))
	class AAIController* _aiController;

};
