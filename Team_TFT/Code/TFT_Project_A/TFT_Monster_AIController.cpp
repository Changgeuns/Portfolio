// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Monster_AIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ATFT_Monster_AIController::ATFT_Monster_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/AI/TFT_Monster_BB_BP.TFT_Monster_BB_BP'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/TFT_Monster_BT_BP.TFT_Monster_BT_BP'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}

void ATFT_Monster_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* blackBoardComponent = Blackboard;
	if (UseBlackboard(_bb, blackBoardComponent))
	{
		if (RunBehaviorTree(_bt))
		{
			blackBoardComponent->SetValueAsVector(FName(TEXT("FixedPos")), InPawn->GetActorLocation());
		}
	}
}

void ATFT_Monster_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATFT_Monster_AIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return;

	FNavLocation randLocation;

	if (naviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	}
}
