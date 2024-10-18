// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_AggroUI.h"
#include "TFT_AggroUI_Slot.h"

#include "Components/VerticalBox.h"

#include "Kismet/KismetMathLibrary.h"

bool UTFT_AggroUI::Initialize()
{
	bool result = Super::Initialize();

	auto array = AggroUI_VB->GetAllChildren();

	for (auto child : array)
	{
		auto slot = Cast<UTFT_AggroUI_Slot>(child);

		if (child)
		{
			_aggroSlots.Add(slot);
			slot->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	return result;
}

void UTFT_AggroUI::SetAggroUI(int32 CauserNum, AActor* DamageCauser, float TotalDamage, float IndividualDamage)
{
	FString name = DamageCauser->GetActorLabel();

	float pbPercent = UKismetMathLibrary::NormalizeToRange(IndividualDamage, 0.0f, TotalDamage);

	_aggroSlots[CauserNum]->SetSlotText(*name);

	_aggroSlots[CauserNum]->SetSlotPBPercent(pbPercent);

	_aggroSlots[CauserNum]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
