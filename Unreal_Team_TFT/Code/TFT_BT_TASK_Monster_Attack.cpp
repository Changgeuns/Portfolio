// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_TASK_Monster_Attack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_Monster_AIController.h"
#include "TFT_Creature.h"
#include "TFT_Monster_Normal.h"
#include "TFT_Player.h"

UTFT_BT_TASK_Monster_Attack::UTFT_BT_TASK_Monster_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UTFT_BT_TASK_Monster_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ATFT_Monster_Normal>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->Attack_AI();
	_isAttacking = true;

	character->_attackEndedDelegate.AddLambda(
		[this]()->void
		{
			this->_isAttacking = false;
		});

	return result;
}

void UTFT_BT_TASK_Monster_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
