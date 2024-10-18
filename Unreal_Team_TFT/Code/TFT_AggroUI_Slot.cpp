// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AggroUI_Slot.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UTFT_AggroUI_Slot::SetSlotText(FString text)
{
	AggroSlotText->SetText(FText::FromString(*text));
}

void UTFT_AggroUI_Slot::SetSlotPBPercent(float percent)
{
	AggroSlotPB->SetPercent(percent);
}
