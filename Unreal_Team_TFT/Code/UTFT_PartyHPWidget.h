// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UTFT_PartyHPWidget.generated.h"


UCLASS()
class TFT_PROJECT_A_API UUTFT_PartyHPWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    virtual void NativeConstruct() override;

    void UpdateArcherHPBar(int32 Index, float HPRatio); 
    void UpdateKnightHPBar(int32 Index, float HPRatio);  

    class UProgressBar* GetHPBarByIndex(int32 Index);

    bool IsOpened();

private:
   
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar1;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar2;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar3;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar4;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar5;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HPBar6;


};
