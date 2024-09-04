// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TFT_BT_Deco_CanAttack.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_BT_Deco_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UTFT_BT_Deco_CanAttack();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
