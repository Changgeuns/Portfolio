// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_Service_TeamAI_SetDist.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "TFT_TeamAI_AIController.h"

UTFT_BT_Service_TeamAI_SetDist::UTFT_BT_Service_TeamAI_SetDist()
{
	NodeName = TEXT("SetDistance");
	Interval = 1.0f;
}

void UTFT_BT_Service_TeamAI_SetDist::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (currentPawn == nullptr) return;

	auto targetPawn = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("Target"))));
	if (targetPawn == nullptr) return;

	float distance = currentPawn->GetDistanceTo(targetPawn);


	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(FName(TEXT("DistanceWithTarget")), distance);
}
