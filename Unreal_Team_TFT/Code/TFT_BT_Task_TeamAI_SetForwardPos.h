// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TFT_BT_Task_TeamAI_SetForwardPos.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_BT_Task_TeamAI_SetForwardPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTFT_BT_Task_TeamAI_SetForwardPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
