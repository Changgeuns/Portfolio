// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TFT_Monster_AIController.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_Monster_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ATFT_Monster_AIController();

	virtual void OnPossess(APawn* InPawn)override;
	virtual void OnUnPossess() override;

	void RandMove();

private:

	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
};
