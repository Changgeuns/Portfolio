// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_Task_TeamAI_SetForwardPos.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_TeamAI_AIController.h"

UTFT_BT_Task_TeamAI_SetForwardPos::UTFT_BT_Task_TeamAI_SetForwardPos()
{
	NodeName = TEXT("SetForwardPos");
}

EBTNodeResult::Type UTFT_BT_Task_TeamAI_SetForwardPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!currentPawn->IsValidLowLevel()) return EBTNodeResult::Type::Failed;

	float currentDistance = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName(TEXT("DistanceWithTarget")));
	float moveDistance = 300.0f;

	while (true)
	{
		currentDistance -= moveDistance;

		if (currentDistance <= 900.0f) break;

		moveDistance += 300.0f;
	}
	
	FVector forwardV = currentPawn->GetActorLocation() + (currentPawn->GetActorForwardVector() * moveDistance);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("ForwardPos")), forwardV);

	return result;
}

void UTFT_BT_Task_TeamAI_SetForwardPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
