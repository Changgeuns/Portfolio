// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_JobChoice.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKnightSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FArcherSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDHSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCGSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBJSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIYSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestSelected);

UCLASS()
class TFT_PROJECT_A_API UTFT_JobChoice : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FKnightSelected _knightSelected;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FArcherSelected _archerSelected;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FDHSelected _DHSelected;
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FCGSelected _CGSelected;
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FBJSelected _BJSelected;
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FIYSelected _IYSelected;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FTestSelected _testSelected;

	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnKnightButtonClicked();
	
	UFUNCTION()
	void OnArcherButtonClicked();

	UFUNCTION()
	void OnDHButtonClicked();
	UFUNCTION()
	void OnCGButtonClicked();
	UFUNCTION()
	void OnBJButtonClicked();
	UFUNCTION()
	void OnIYButtonClicked();

	UFUNCTION()
	void OnTestButtonClicked();

private:
	void HideUI();
};
