// Fill out your copyright notice in the Description page of Project Settings.


#include "UTFT_PartyHPWidget.h"
#include "Components/ProgressBar.h"

void UUTFT_PartyHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUTFT_PartyHPWidget::UpdateArcherHPBar(int32 Index, float HPRatio)
{
    UProgressBar* HPBar = GetHPBarByIndex(Index);  
    if (HPBar)
    {
        HPBar->SetPercent(HPRatio);
    }
}

void UUTFT_PartyHPWidget::UpdateKnightHPBar(int32 Index, float HPRatio)
{
    UProgressBar* HPBar = GetHPBarByIndex(Index + 3);  
    if (HPBar)
    {
        HPBar->SetPercent(HPRatio);
    }
}

UProgressBar* UUTFT_PartyHPWidget::GetHPBarByIndex(int32 Index)
{
    switch (Index)
    {
    case 0: return HPBar1;
    case 1: return HPBar2;
    case 2: return HPBar3;
    case 3: return HPBar4;
    case 4: return HPBar5;
    case 5: return HPBar6;
    default: return nullptr;
    }
}

bool UUTFT_PartyHPWidget::IsOpened()
{
    return this->IsInViewport();
}

