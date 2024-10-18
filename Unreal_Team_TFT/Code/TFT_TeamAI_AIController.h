// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TFT_TeamAI_AIController.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TeamAI_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ATFT_TeamAI_AIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;


private:
	UPROPERTY()
	class UBlackboardData* _bb;
	UPROPERTY()
	class UBehaviorTree* _btA;
	UPROPERTY()
	class UBehaviorTree* _btK;
	
};
