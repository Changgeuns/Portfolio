// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_TM_SkillSlot.generated.h"

UCLASS()
class TFT_PROJECT_A_API UTFT_TM_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetSlotNumText(FString text);

	void SetSlotImg(int32 itemId);
	void ResetSlotImg();

	void SetSlotPBPercent(float percent);

	void SetCDT(float CDT);

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	bool bCoolDownOn = false;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillSlotNumText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SkillSlotPB;

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillSlotImg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	float _coolDownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	float _runTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	UObject* _brushQ_Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	UObject* _brushE_Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	UObject* _nullBrush_Resource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	FSlateBrush _brushQ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	FSlateBrush _brushE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillSlot, meta = (AllowPrivateAccess = "true"))
	FSlateBrush _nullBrush;
	
};
