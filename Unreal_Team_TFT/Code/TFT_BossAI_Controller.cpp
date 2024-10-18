// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_BossAI_Controller.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ATFT_BossAI_Controller::ATFT_BossAI_Controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/AI/TFT_Boss_BB_BP.TFT_Boss_BB_BP'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/TFT_Boss_BT_BP.TFT_Boss_BT_BP'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}

void ATFT_BossAI_Controller::OnPossess(APawn* InPawn)
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

void ATFT_BossAI_Controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATFT_BossAI_Controller::RandMove()
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
