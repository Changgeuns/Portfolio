// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TFT_BT_Service_TeamAI_FindTarget.generated.h"

UCLASS()
class TFT_PROJECT_A_API UTFT_BT_Service_TeamAI_FindTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UTFT_BT_Service_TeamAI_FindTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SetPlayer(UBehaviorTreeComponent& OwnerComp);
};
