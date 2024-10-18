// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TB_AIController_CG.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ATFT_TB_AIController_CG::ATFT_TB_AIController_CG()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/Monster/CG/AI/TFT_Boss_BB_BP_CG.TFT_Boss_BB_BP_CG'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/Monster/CG/AI/TFT_Boss_BT_BP_CG.TFT_Boss_BT_BP_CG'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}

void ATFT_TB_AIController_CG::OnPossess(APawn* InPawn)
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

void ATFT_TB_AIController_CG::OnUnPossess()
{
	Super::OnUnPossess();
}

void ATFT_TB_AIController_CG::RandMove()
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
