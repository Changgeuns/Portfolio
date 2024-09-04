// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_TASK_Boss_Attack.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_BossAI_Controller.h"
#include "TFT_Creature.h"
#include "TFT_Monster_Boss.h"
#include "TFT_Player.h"

UTFT_BT_TASK_Boss_Attack::UTFT_BT_TASK_Boss_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UTFT_BT_TASK_Boss_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<ATFT_Monster_Boss>(OwnerComp.GetAIOwner()->GetPawn());
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

void UTFT_BT_TASK_Boss_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
