// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_AggroUI.generated.h"

class UProgressBar;
class UTFT_AggroUI_Slot;
class UVerticalBox;

UCLASS()
class TFT_PROJECT_A_API UTFT_AggroUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	void SetAggroUI(int32 CauserNum, AActor* DamageCauser, float TotalDamage, float IndividualDamage);

public:
	TArray<UTFT_AggroUI_Slot*> _aggroSlots;
	
	UPROPERTY(meta = (NindWidget))
	UVerticalBox* AggroUI_VB;
};
