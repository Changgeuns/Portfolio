// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BT_Service_TeamAI_FindTarget.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "TFT_TeamAI_AIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "TFT_Monster.h"
#include "TFT_Player.h"


UTFT_BT_Service_TeamAI_FindTarget::UTFT_BT_Service_TeamAI_FindTarget()
{
	NodeName = TEXT("FindTarget");
	Interval = 0.5f;
}

void UTFT_BT_Service_TeamAI_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SetPlayer(OwnerComp);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (currentPawn == nullptr) return;

	auto world = GetWorld();
	if (world == nullptr) return;

	FVector center = currentPawn->GetActorLocation();
	float searchRadius = 1000.0f;
	
	TArray<FOverlapResult> overlapResult;
	FCollisionQueryParams qParams(NAME_None, false, currentPawn);

	bool bResult = world->OverlapMultiByChannel
	(
		overlapResult,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel4,
		FCollisionShape::MakeSphere(searchRadius),
		qParams
	);

	if (bResult)
	{
		for (auto& result : overlapResult)
		{
			auto target = Cast<ATFT_Monster>(result.GetActor());

			if (target != nullptr)
			{
				auto targetController = target->GetController();
				
				if (targetController != nullptr)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), target);


					return;
				}
			}
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);

	}
}

void UTFT_BT_Service_TeamAI_FindTarget::SetPlayer(UBehaviorTreeComponent& OwnerComp)
{
	auto player = Cast<ATFT_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (player != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Player")), player);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Player")), nullptr);
	}
}
