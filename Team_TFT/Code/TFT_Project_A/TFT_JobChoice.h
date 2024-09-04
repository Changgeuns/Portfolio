// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_JobChoice.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKnightSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArcherSelected);

UCLASS()
class TFT_PROJECT_A_API UTFT_JobChoice : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FKnightSelected _knightSelected;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FArcherSelected _archerSelected;

	
	virtual void NativeConstruct() override;

	
	UFUNCTION()
	void OnKnightButtonClicked();

	
	UFUNCTION()
	void OnArcherButtonClicked();

private:
	void HideUI();
};
