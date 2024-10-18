// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_HpBar.h"
#include "Components/ProgressBar.h"

void UTFT_HpBar::SetHpBarValue(float ratio)
{
	PB_HpBar->SetPercent(ratio);
}

void UTFT_HpBar::SetMpBarValue(float ratio)
{
	PB_MpBar->SetPercent(ratio);
}

void UTFT_HpBar::SetExpBarValue(float ratio)
{
	PB_ExpBar->SetPercent(ratio);
}
