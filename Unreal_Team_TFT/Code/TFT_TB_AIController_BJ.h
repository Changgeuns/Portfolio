// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TFT_TB_AIController_BJ.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TB_AIController_BJ : public AAIController
{
	GENERATED_BODY()
public:
	ATFT_TB_AIController_BJ();

	virtual void OnPossess(APawn* InPawn)override;
	virtual void OnUnPossess() override;

	void RandMove();

private:

	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
};
