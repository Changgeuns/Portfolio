// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_InvenUI.h"

#include "TFT_Item.h"
#include "TFT_InvenComponent.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "TFT_UIManager.h"

bool UTFT_InvenUI::Initialize()
{
	bool abc = Super::Initialize();

	auto array = Inven_UniformGrid->GetAllChildren();
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
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView0);
				break;
			}
			case 1:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView1);
				break;
			}
			case 2:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView2);
				break;
			}
			case 3:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView3);
				break;
			}
			case 4:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView4);
				break;
			}
			case 5:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView5);
				break;
			}
			case 6:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView6);
				break;
			}
			case 7:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView7);
				break;
			}
			case 8:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_InvenUI::SetToDetailView8);
				break;
			}
			default:
				break;
			}
		}
		slotIndex++;
	}

	Exit_Button->OnClicked.AddDynamic(this, &UTFT_InvenUI::InvenOpenClose);

	Drop_Button->OnClicked.AddDynamic(this, &UTFT_InvenUI::DropItem);

	_UIsaveiteminfo.SetNum(9);

	_emptySlot = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/ParagonSparrow/Characters/Global/MaterialLayers/Fabric/T_ML_Fabric_Shiny_Gray.T_ML_Fabric_Shiny_Gray'"));

	Item_Information->SetText(_nullText);
	Inven_ItemMiniInfo->SetText(_nullText);
	Inven_ItemExplanation->SetText(_nullText);

	return abc;
}

void UTFT_InvenUI::InvenOpenClose()
{
	_CloseInvenBtn.Broadcast();
}


void UTFT_InvenUI::DropItem()
{
	if (this_Index == -1)
	{
		UE_LOG(LogTemp, Log, TEXT("Your Not Choice Item"));
		return;
	}
	else
	{
		_SlotItemEvent.Broadcast(_this_Item, this_Index);
		SetItemSlot(_emptySlot, this_Index);
		DetailViewImg->SetBrushFromTexture(_emptySlot);
		DeleteUIItem(this_Index);
	}
}

void UTFT_InvenUI::SetItemSlot(UTexture2D* texture, int32 slotIndex)
{
	_slotBtns[slotIndex]->WidgetStyle.Normal.SetResourceObject(texture);
}

void UTFT_InvenUI::AddUiItem(ATFT_Item* item, int32 index)
{
	UE_LOG(LogTemp, Log, TEXT("AddUIItem In"));
	if (!item)
	{
		UE_LOG(LogTemp, Log, TEXT("NO ITem"));
	}
	SetItemSlot(item->GetMyTexture(), index);
	_UIsaveiteminfo[index] = item;
}

void UTFT_InvenUI::SelectSlotItem(int32 index)
{
	if (_UIsaveiteminfo[index] != nullptr)
	{
		_this_Item = _UIsaveiteminfo[index];
		this_Index = index;
		UISetItemName(index);
		UISetItemMiniInfo(index);
		UISetItemExplanation(index);
		DetailViewImg->SetBrushFromTexture(_this_Item->GetMyTexture());
	}
	else
	{
		DetailViewImg->SetBrushFromTexture(_emptySlot);
		Item_Information->SetText(_nullText);
		Inven_ItemMiniInfo->SetText(_nullText);
		Inven_ItemExplanation->SetText(_nullText);
		this_Index = -1;
		_this_Item = nullptr;
	}


}

void UTFT_InvenUI::SetToDetailView0()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 1"));
	SelectSlotItem(0);
}

void UTFT_InvenUI::SetToDetailView1()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 2"));
	SelectSlotItem(1);
}

void UTFT_InvenUI::SetToDetailView2()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 3"));
	SelectSlotItem(2);
}

void UTFT_InvenUI::SetToDetailView3()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 4"));
	SelectSlotItem(3);
}

void UTFT_InvenUI::SetToDetailView4()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 5"));
	SelectSlotItem(4);
}

void UTFT_InvenUI::SetToDetailView5()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 6"));
	SelectSlotItem(5);
}

void UTFT_InvenUI::SetToDetailView6()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 7"));
	SelectSlotItem(6);
}

void UTFT_InvenUI::SetToDetailView7()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 8"));
	SelectSlotItem(7);
}

void UTFT_InvenUI::SetToDetailView8()
{
	UE_LOG(LogTemp, Log, TEXT("Slot : 9"));
	SelectSlotItem(8);
}

void UTFT_InvenUI::DeleteUIItem(int32 index)
{
	_UIsaveiteminfo[index] = nullptr;
	_this_Item = nullptr;
	this_Index = -1;
}

void UTFT_InvenUI::UISetItemName(int32 index)
{
	
	FString ItemNameString = FString::Printf(TEXT("%s"), *_UIsaveiteminfo[index]->GetItemName());
	FText ItemName = FText::FromString(ItemNameString);

	Item_Information->SetText(ItemName);
}

void UTFT_InvenUI::UISetItemMiniInfo(int32 index)
{
	FString ItemMiniString = FString::Printf(TEXT("%s"), *_UIsaveiteminfo[index]->GetItemMiniInfo());
	FText ItemMiniInfo = FText::FromString(ItemMiniString);

	Inven_ItemMiniInfo->SetText(ItemMiniInfo);
}

void UTFT_InvenUI::UISetItemExplanation(int32 index)
{
	FString ItemExString = FString::Printf(TEXT("%s"), *_UIsaveiteminfo[index]->GetItemExplanation());
	FText ItemExplanation = FText::FromString(ItemExString);

	Inven_ItemExplanation->SetText(ItemExplanation);
}

void UTFT_InvenUI::UIGold(int32 gold) 
{
	FString InvenGoldString = FString::Printf(TEXT("%d Gold"), gold);
	FText InvenUIGolds = FText::FromString(InvenGoldString);

	Inven_UIGold->SetText(InvenUIGolds);
}
