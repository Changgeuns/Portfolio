// Fill out your copyright notice in the Description page of Project Settings.

#include "TFT_TM_SkillUI.h"
#include "TFT_TM_SkillSlot.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"

bool UTFT_TM_SkillUI::Initialize()
{
	bool result = Super::Initialize();

	auto array = SkillUI_HB->GetAllChildren();
	

	for (auto child : array)
	{
		auto slot = Cast<UTFT_TM_SkillSlot>(child);
		
		if (slot)
		{
			_skillSlots.Add(slot);
		}	
	}

	
	for (int32 i = 0; i < _skillSlots.Num(); i++)
	{
		if (i == 0) _skillSlots[i]->SetSlotNumText("Q");
		if (i == 1) _skillSlots[i]->SetSlotNumText("E");

	}

	return result;
}

void UTFT_TM_SkillUI::SetSkillSlot(int32 slotNum, float CoolDownTime, int32 itemId)
{
	_skillSlots[slotNum]->SetCDT(CoolDownTime);
	_skillSlots[slotNum]->SetSlotImg(itemId);
}

void UTFT_TM_SkillUI::ResetSkillSlot(int32 slotNum)
{
	_skillSlots[slotNum]->ResetSlotImg();
}

void UTFT_TM_SkillUI::RunCDT(int32 slotNum)
{
	if (_skillSlots[slotNum]->bCoolDownOn == false)
	{
		_skillSlots[slotNum]->bCoolDownOn = true;
	}
}
