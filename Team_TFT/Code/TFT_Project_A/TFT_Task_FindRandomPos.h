// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TFT_Task_FindRandomPos.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_Task_FindRandomPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTFT_Task_FindRandomPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
};
