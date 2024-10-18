// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_Equipment_Window.h"
#include "TFT_Item.h"
#include "TFT_InvenComponent.h"
#include "TFT_InvenUI.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

#include "TFT_GameInstance.h"
#include "TFT_UIManager.h"
#include "TFT_TM_SkillUI.h"

#include "TFT_Player.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Input/Reply.h"
#include "Input/Events.h"

bool UTFT_Equipment_Window::Initialize()
{
	bool abc = Super::Initialize();

	auto array = TFT_Equipment->GetAllChildren();
	int32 slotIndex = 0;

	for (auto slot : array)
	{
		auto btn = Cast<UButton>(slot);
		if (btn)
		{
			_slotBtns.Add(btn);

			switch (slotIndex)
			{
			case 0:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_Head);
				break;
			}
			case 1:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_Chest);
				break;
			}
			case 2:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_Leg);
				break;
			}
			case 3:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_Foot);
				break;
			}
			case 4:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_R_Weapon);
				break;
			}
			case 5:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::SetTo_L_Weapon);
				break;
			}
			default:
				break;
			}

		}
		slotIndex++;
	}
	_EquipmentItem.SetNum(6);

	TakeOff_Button->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::Set_TakeOff);

	Exit_Button->OnClicked.AddDynamic(this, &UTFT_Equipment_Window::EquipmentBtnClose);


	_emptySlot = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/BluePrint/Player/ChangGeun/CG_texture/invisible.invisible'"));

	_choiceSlot = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/BluePrint/Player/ChangGeun/CG_texture/Choice.Choice'"));



	return abc;
}

void UTFT_Equipment_Window::EquipmentBtnClose()
{
	_CloseEquipmentBtn.Broadcast();
}

void UTFT_Equipment_Window::Set_TakeOff()
{
	if (this_Item == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Not Choice Item"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("TAkeOff~"));

		_ItemChangeEvent.Broadcast(this_Item);
		Un_Equipment(this_Index);
		SetItemChoice(_emptySlot, this_Index);

		choiceCheck = false;
		_EquipmentItem[this_Index] = nullptr;
		this_Item = nullptr;
		this_Index = -1;

		UIMANAGER->GetSkillUI()->ResetSkillSlot(0);
		UIMANAGER->GetSkillUI()->ResetSkillSlot(1);
	}
}

void UTFT_Equipment_Window::SelectSlotItem(int32 index)
{
	if (_EquipmentItem[index] != nullptr)
	{
		if (choiceCheck == true)
		{
			SetItemChoice(_emptySlot, this_Index);
			choiceCheck = false;
		}
		this_Item = _EquipmentItem[index];
		this_Index = index;

		SetItemChoice(_choiceSlot, index);

	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Item"));
	}
}

void UTFT_Equipment_Window::SetTo_Head()
{
	UE_LOG(LogTemp, Log, TEXT("Head"));
	SelectSlotItem(0);
}

void UTFT_Equipment_Window::SetTo_Chest()
{
	UE_LOG(LogTemp, Log, TEXT("Chest"));
	SelectSlotItem(1);
}

void UTFT_Equipment_Window::SetTo_Leg()
{
	UE_LOG(LogTemp, Log, TEXT("Leg"));
	SelectSlotItem(2);
}

void UTFT_Equipment_Window::SetTo_Foot()
{
	UE_LOG(LogTemp, Log, TEXT("Foot"));
	SelectSlotItem(3);
}

void UTFT_Equipment_Window::SetTo_R_Weapon()
{
	UE_LOG(LogTemp, Log, TEXT("R_Weapon"));
	SelectSlotItem(4);
}

void UTFT_Equipment_Window::SetTo_L_Weapon()
{
	UE_LOG(LogTemp, Log, TEXT("L_Weapon"));
	SelectSlotItem(5);
}

void UTFT_Equipment_Window::Set_Equipment(ATFT_Item* item)
{
	auto player = Cast<ATFT_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (item->GetItemRegion() == "Head")
	{
		Changes(item, 0);
		Use_Head->SetBrushFromTexture(item->GetMyTexture());
	}
	else if (item->GetItemRegion() == "Chest")
	{
		Changes(item, 1);
		Use_Chest->SetBrushFromTexture(item->GetMyTexture());
	}
	else if (item->GetItemRegion() == "Leg")
	{
		Changes(item, 2);
		Use_Leg->SetBrushFromTexture(item->GetMyTexture());
	}
	else if (item->GetItemRegion() == "Foot")
	{
		Changes(item, 3);
		Use_Foot->SetBrushFromTexture(item->GetMyTexture());
	}
	else if (item->GetItemRegion() == "R_Weapon")
	{
		Changes(item, 4);
		Use_RWeapon->SetBrushFromTexture(item->GetMyTexture());

		player->_invenCom->SetWeapon(item);
	}
	else if (item->GetItemRegion() == "L_Weapon")
	{
		Changes(item, 5);
		Use_LWeapon->SetBrushFromTexture(item->GetMyTexture());
	}
	else
	{
		return;
	}
}

void UTFT_Equipment_Window::Un_Equipment(int32 index)
{
	switch (index)
	{
	case 0:
	{
		Use_Head->SetBrushFromTexture(_emptySlot);
	}
	break;
	case 1:
	{
		Use_Chest->SetBrushFromTexture(_emptySlot);
	}
	break;
	case 2:
	{
		Use_Leg->SetBrushFromTexture(_emptySlot);
	}
	break;
	case 3:
	{
		Use_Foot->SetBrushFromTexture(_emptySlot);
	}
	break;
	case 4:
	{
		Use_RWeapon->SetBrushFromTexture(_emptySlot);
	}
	break;
	case 5:
	{
		Use_LWeapon->SetBrushFromTexture(_emptySlot);
	}
	break;
	default:
		break;
	}
}

void UTFT_Equipment_Window::Changes(ATFT_Item* item, int32 index)
{
	if (_EquipmentItem[index] != nullptr)
	{
		_ItemChangeEvent.Broadcast(_EquipmentItem[index]);

		_EquipmentItem[index] = item;
		Use_RWeapon->SetBrushFromTexture(item->GetMyTexture());
		_ItemChangeEvent_stat.Broadcast(item);

		return;
	}
	else
	{
		_EquipmentItem[index] = item;
		_ItemChangeEvent_stat.Broadcast(item);
	}
}

void UTFT_Equipment_Window::SetItemChoice(UTexture2D* texture, int32 slotIndex)
{
	choiceCheck = true;
	_slotBtns[slotIndex]->WidgetStyle.Normal.SetResourceObject(texture);
}

void UTFT_Equipment_Window::ResetChoice()
{
	if (this_Item != nullptr)
	{
		_slotBtns[this_Index]->WidgetStyle.Normal.SetResourceObject(_emptySlot);

		this_Index = -1;
		this_Item = nullptr;
	}
}

