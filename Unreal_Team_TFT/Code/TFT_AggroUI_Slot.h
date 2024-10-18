// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_AggroUI_Slot.generated.h"


UCLASS()
class TFT_PROJECT_A_API UTFT_AggroUI_Slot : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSlotText(FString text);
	void SetSlotPBPercent(float percent);
	
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* AggroSlotText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* AggroSlotPB;

};
