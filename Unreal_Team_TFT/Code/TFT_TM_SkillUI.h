// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_TM_SkillUI.generated.h"

class UProgressBar;
class UTexture2D;
class UTFT_TM_SkillSlot;
class UHorizontalBox;

UCLASS()
class TFT_PROJECT_A_API UTFT_TM_SkillUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UTFT_TM_SkillSlot* GetSkillSlot(int32 slotNum) { return _skillSlots[slotNum]; }
	
	void SetSkillSlot(int32 slotNum, float CoolDownTime, int32 itemId); 
	void ResetSkillSlot(int32 slotNum);


	void RunCDT(int32 slotNum);

private:

public:
	TArray<UTexture2D*> _skillImgs;

	TArray<UTFT_TM_SkillSlot*> _skillSlots;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SkillUI_HB;
};
