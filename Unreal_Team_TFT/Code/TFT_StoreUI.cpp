// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_StoreUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

#include "TFT_Player.h"
#include "TFT_InvenComponent.h"
#include "TFT_Item.h"

#include "TFT_GameInstance.h"
#include "TFT_UIManager.h"
#include "TFT_InvenUI.h"

bool UTFT_StoreUI::Initialize()
{
	bool abc = Super::Initialize();

	auto array = Store_UniformGrid->GetAllChildren();
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
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView0);
				break;
			}
			case 1:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView1);
				break;
			}
			case 2:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView2);
				break;
			}
			case 3:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView3);
				break;
			}
			case 4:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView4);
				break;
			}
			case 5:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView5);
				break;
			}
			case 6:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView6);
				break;
			}
			case 7:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView7);
				break;
			}
			case 8:
			{
				btn->OnClicked.AddDynamic(this, &UTFT_StoreUI::SetToDetailView8);
				break;
			}
			default:
				break;
			}
		}
		slotIndex++;
	}

	Exit_Button->OnClicked.AddDynamic(this, &UTFT_StoreUI::StoreClose);

	Purchase_Button->OnClicked.AddDynamic(this, &UTFT_StoreUI::PurchaseItem);

	_Storesaveiteminfo.SetNum(9);

	_emptySlot = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/ParagonSparrow/Characters/Global/MaterialLayers/Fabric/T_ML_Fabric_Shiny_Gray.T_ML_Fabric_Shiny_Gray'"));


	SetVisibility(ESlateVisibility::Collapsed);

	return abc;
}

void UTFT_StoreUI::StoreOpen()
{
	if(bIsOpen == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Store Open!!"));
		SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		bIsOpen = true;

		UIMANAGER->GetInvenUI()->storeCheke = bIsOpen;
		UIMANAGER->GetInvenUI()->Store_DropSellTextCheck();
		return;
	}
}

void UTFT_StoreUI::StoreClose()
{
	if (bIsOpen == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Store Close!!"));
		SetVisibility(ESlateVisibility::Collapsed);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		bIsOpen = false;

		UIMANAGER->GetInvenUI()->storeCheke = bIsOpen;
		UIMANAGER->GetInvenUI()->Store_DropSellTextCheck();
		return;
	}
}

void UTFT_StoreUI::PurchaseItem()
{
	

	if (this_Index == -1)
	{
		UE_LOG(LogTemp, Log, TEXT("Your Not Choice Item"));
		return;
	}
	else
	{
		_ItemBuy.Broadcast(_this_Item, this_Index);

	}
}

void UTFT_StoreUI::SelectSlotStoreItem(int32 index)
{
	if (_Storesaveiteminfo[index] != nullptr)
	{
		_this_Item = _Storesaveiteminfo[index];
		this_Index = index;
		UISetItemName(index);
		UISetItemMiniInfo(index);
		UISetItemPrice(index);
		DetailViewImg->SetBrushFromTexture(_this_Item->GetMyTexture());
	}
	else
	{
		DetailViewImg->SetBrushFromTexture(_emptySlot);
		Item_Information->SetText(_nullText);
		Item_miniInfo->SetText(_nullText);
		Item_Price->SetText(_nullText);
		_this_Item = nullptr;
		this_Index = -1;
	}
}

void UTFT_StoreUI::SetItemSlot(UTexture2D* texture, int32 slotIndex)
{
	_slotBtns[slotIndex]->WidgetStyle.Normal.SetResourceObject(texture);
}

void UTFT_StoreUI::SetStoreItem(ATFT_Item* items, int32 index)
{
	_Storesaveiteminfo[index] = items;

	SetItemSlot(items->GetMyTexture(), index);
}

void UTFT_StoreUI::SetToDetailView0()
{


	SelectSlotStoreItem(0);
}

void UTFT_StoreUI::SetToDetailView1()
{


	SelectSlotStoreItem(1);
}

void UTFT_StoreUI::SetToDetailView2()
{

	SelectSlotStoreItem(2);
}

void UTFT_StoreUI::SetToDetailView3()
{


	SelectSlotStoreItem(3);
}

void UTFT_StoreUI::SetToDetailView4()
{


	SelectSlotStoreItem(4);
}

void UTFT_StoreUI::SetToDetailView5()
{


	SelectSlotStoreItem(5);
}

void UTFT_StoreUI::SetToDetailView6()
{


	SelectSlotStoreItem(6);
}

void UTFT_StoreUI::SetToDetailView7()
{


	SelectSlotStoreItem(7);
}

void UTFT_StoreUI::SetToDetailView8()
{


	SelectSlotStoreItem(8);
}

void UTFT_StoreUI::UISetItemName(int32 index)
{
	FString ItemString = FString::Printf(TEXT("%s"), *_Storesaveiteminfo[index]->GetItemName());
	FText ItemName = FText::FromString(ItemString);

	Item_Information->SetText(ItemName);
}

void UTFT_StoreUI::UISetItemMiniInfo(int32 index)
{
	FString ItemMiniString = FString::Printf(TEXT("%s"), *_Storesaveiteminfo[index]->GetItemMiniInfo());
	FText ItemMiniInfo = FText::FromString(ItemMiniString);

	Item_miniInfo->SetText(ItemMiniInfo);
}

void UTFT_StoreUI::UISetItemPrice(int32 index)
{
	FString itemPriceString = FString::Printf(TEXT("Price : %d Gold"), _Storesaveiteminfo[index]->GetItemGold());
	FText itemPrice = FText::FromString(itemPriceString);

	Item_Price->SetText(itemPrice);
}

