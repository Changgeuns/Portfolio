// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TM_SkillSlot.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Slate\SlateBrushAsset.h"

#include "Kismet/KismetMathLibrary.h"

void UTFT_TM_SkillSlot::NativePreConstruct()
{
	Super::NativePreConstruct();


}

void UTFT_TM_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	_brushQ_Resource = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_bone_05_b.Tex_bone_05_b'"));
	_brushE_Resource = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_bone_08_b.Tex_bone_08_b'"));
	_nullBrush_Resource = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/ParagonSparrow/Characters/Global/MaterialLayers/Fabric/T_ML_Fabric_Shiny_Gray.T_ML_Fabric_Shiny_Gray'"));

	_brushQ.SetResourceObject(_brushQ_Resource);
	_brushE.SetResourceObject(_brushE_Resource);
	_nullBrush.SetResourceObject(_nullBrush_Resource);

	SkillSlotImg->SetBrush(_nullBrush);
}

void UTFT_TM_SkillSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_runTime >= _coolDownTime)
	{
		_runTime = 0.0f;
		bCoolDownOn = false;

		return;
	}

	if (bCoolDownOn)
	{
		_runTime += InDeltaTime;

		float pbPercent = 1.0f - UKismetMathLibrary::NormalizeToRange(_runTime, 0.0f, _coolDownTime);

		SetSlotPBPercent(pbPercent);
	}
}

void UTFT_TM_SkillSlot::SetSlotNumText(FString text)
{
	

	SkillSlotNumText->SetText(FText::FromString(*text));
}

void UTFT_TM_SkillSlot::SetSlotImg(int32 itemId)
{
	if (itemId == 1)
	{
		SkillSlotImg->SetBrush(_brushQ);
	}

	if (itemId == 3)
	{
		SkillSlotImg->SetBrush(_brushE);
	}
}

void UTFT_TM_SkillSlot::ResetSlotImg()
{
	SkillSlotImg->SetBrush(_nullBrush);
}

void UTFT_TM_SkillSlot::SetSlotPBPercent(float percent)
{
	SkillSlotPB->SetPercent(percent);

}

void UTFT_TM_SkillSlot::SetCDT(float CDT)
{
	_coolDownTime = CDT;
}
