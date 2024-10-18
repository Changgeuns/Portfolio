// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_Task_FindRangedPos.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_TeamAI_AIController.h"

UTFT_BT_Task_FindRangedPos::UTFT_BT_Task_FindRangedPos()
{
	NodeName = TEXT("FindRangedPos");
}

EBTNodeResult::Type UTFT_BT_Task_FindRangedPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!currentPawn->IsValidLowLevel()) return EBTNodeResult::Type::Failed;

	auto targetPawn = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if(targetPawn == nullptr) return EBTNodeResult::Type::Failed;

	auto naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if(naviSystem == nullptr) return EBTNodeResult::Type::Failed;

	FNavLocation randLocation;

	if (naviSystem->GetRandomReachablePointInRadius(currentPawn->GetActorLocation(), 1500.0f, randLocation))
	{
		float distance = (targetPawn->GetActorLocation() - randLocation).Length();

		if (distance > 600.0f)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RangedPos")), randLocation);

			return result = EBTNodeResult::Type::Succeeded;
		}
		else
		{
			return result = EBTNodeResult::Type::Succeeded;
		}
	}

	return result;
}

void UTFT_BT_Task_FindRangedPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
