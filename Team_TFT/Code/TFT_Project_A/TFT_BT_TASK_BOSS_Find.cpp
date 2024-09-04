// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_TASK_BOSS_Find.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_BossAI_Controller.h"

UTFT_BT_TASK_BOSS_Find::UTFT_BT_TASK_BOSS_Find()
{
	NodeName = TEXT("FindRandPos");
}

EBTNodeResult::Type UTFT_BT_TASK_BOSS_Find::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return EBTNodeResult::Type::Failed;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return EBTNodeResult::Type::Failed;

	FNavLocation randLocation;

	FVector fixedPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("fixedPos")));

	if (naviSystem->GetRandomPointInNavigableRadius(fixedPos, 1500.0f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation);
		return EBTNodeResult::Type::Succeeded;
	}

	return result;
}
