// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFT_UIManager.generated.h"


class UUserWidget;
class UTFT_InvenUI;

DECLARE_MULTICAST_DELEGATE(InvenOpen);

UENUM()
enum class UIType : int32
{
	CrossHair,
	Inventory,
};


UCLASS()
class TFT_PROJECT_A_API ATFT_UIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATFT_UIManager();

protected:

	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;



	void OpenWidget(UIType type);
	void CloseWidget(UIType type);
	void CloseAll();

	UFUNCTION()
	void OpenInvenUIA();
	UFUNCTION()
	void CloseInvenBtn();

	UTFT_InvenUI* GetInvenUI() { return _invenWidget; }

	InvenOpen _invenOpenEvent;

private:
	UPROPERTY()
	TArray<UUserWidget*> _widgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UTFT_InvenUI* _invenWidget;

	bool _UIarea = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUserWidget* _crossHair;
};
