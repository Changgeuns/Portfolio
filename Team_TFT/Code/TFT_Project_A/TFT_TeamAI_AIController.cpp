// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TeamAI_AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

#include "TFT_TeamAI_Archer.h"
#include "TFT_TeamAI_Knight.h"

ATFT_TeamAI_AIController::ATFT_TeamAI_AIController()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData> BBD
	(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/AI/TFT_TeamAI_BB_BP.TFT_TeamAI_BB_BP'"));
	if (BBD.Succeeded())
	{
		_bb = BBD.Object;
	}



	ConstructorHelpers::FObjectFinder<UBehaviorTree> BHT_A
	(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/TFT_TeamAI_Archer_BT_BP.TFT_TeamAI_Archer_BT_BP'"));
	if (BHT_A.Succeeded())
	{
		_btA = BHT_A.Object;
	}

	ConstructorHelpers::FObjectFinder<UBehaviorTree> BHT_K
	(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrint/AI/TFT_TeamAI_Knight_BT_BP.TFT_TeamAI_Knight_BT_BP'"));
	if (BHT_K.Succeeded())
	{
		_btK = BHT_K.Object;
	}
}

void ATFT_TeamAI_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto teamAI = Cast<ATFT_TeamAI_Archer>(GetPawn());

	UBlackboardComponent* bbCom = Blackboard;
	
	if (UseBlackboard(_bb, bbCom))
	{
		if (teamAI != nullptr)
		{
			if (RunBehaviorTree(_btA))
			{
				UE_LOG(LogTemp, Log, TEXT("Archer Behavior Tree Succeeded."));
			}
		}
		else
		{
			if (RunBehaviorTree(_btK))
			{
				UE_LOG(LogTemp, Log, TEXT("Knight Behavior Tree Succeeded."));
			}
		}
	}
}

void ATFT_TeamAI_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}


