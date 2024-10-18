// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TFT_BT_TASK_BOSS_Find.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_BT_TASK_BOSS_Find : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTFT_BT_TASK_BOSS_Find();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
};
