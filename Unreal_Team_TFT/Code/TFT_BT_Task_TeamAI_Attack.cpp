// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_Task_TeamAI_Attack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_TeamAI_AIController.h"
#include "TFT_TeamAI.h"

UTFT_BT_Task_TeamAI_Attack::UTFT_BT_Task_TeamAI_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UTFT_BT_Task_TeamAI_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto teamAI = Cast<ATFT_TeamAI>(OwnerComp.GetAIOwner()->GetPawn());
	if (teamAI == nullptr) return EBTNodeResult::Failed;

	teamAI->Attack_AI();
	_isAttacking = true;

	teamAI->_attackEndedDelegate.AddLambda(
		[this]()->void
		{
			this->_isAttacking = false;
		});

	return result;
}

void UTFT_BT_Task_TeamAI_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
