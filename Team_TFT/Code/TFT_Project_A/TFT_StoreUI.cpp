// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_StoreUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"


void UTFT_StoreUI::NativeConstruct()
{
	Super::NativeConstruct();

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

	Exit_Button->OnClicked.AddDynamic(this, &UTFT_StoreUI::StoreOpenClose);

	Purchase_Button->OnClicked.AddDynamic(this, &UTFT_StoreUI::PurchaseItem);

	
	_emptySlot = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/ParagonSparrow/Characters/Global/MaterialLayers/Fabric/T_ML_Fabric_Shiny_Gray.T_ML_Fabric_Shiny_Gray'"));

	_redGem = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_gemstone_01_b.Tex_gemstone_01_b'"));
	_itemImgs.Add(_redGem);

	_blueGem = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_gemstone_06_b.Tex_gemstone_06_b'"));
	_itemImgs.Add(_blueGem);

	_emeraldGem = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_gemstone_03_b.Tex_gemstone_03_b'"));
	_itemImgs.Add(_emeraldGem);

	_purplePotion = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_reagent_10_b.Tex_reagent_10_b'"));
	_itemImgs.Add(_purplePotion);

	_wildGinseng = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_seeds_04_b.Tex_seeds_04_b'"));
	_itemImgs.Add(_wildGinseng);

	_greenSoup = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_reagent_07_b.Tex_reagent_07_b'"));
	_itemImgs.Add(_greenSoup);

	_shield = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_spare_parts_06_b.Tex_spare_parts_06_b'"));
	_itemImgs.Add(_shield);

	_arrowHead = LoadObject<UTexture2D>
		(nullptr, TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_ingots_08_b.Tex_ingots_08_b'"));
	_itemImgs.Add(_arrowHead);

	SetVisibility(ESlateVisibility::Collapsed);

	SetToDetailView8();
}

void UTFT_StoreUI::StoreOpenClose()
{
	if (bIsOpen == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Store Close!!"));
		SetVisibility(ESlateVisibility::Collapsed);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		bIsOpen = false;
		return;
	}
	else if(bIsOpen == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Store Open!!"));
		SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		bIsOpen = true;
		return;
	}
}

void UTFT_StoreUI::PurchaseItem()
{
	_purchaseDelegateOneParam.Broadcast(_itemSlot);

}

void UTFT_StoreUI::SetItemSlot(int32 itemId, int32 slotIndex)
{
	if (_itemImgs.IsEmpty()
		|| !_slotBtns.IsValidIndex(slotIndex)
		|| !_itemImgs.IsValidIndex(itemId)) return;

	if (itemId == -1)
	{
		_slotBtns[slotIndex]->WidgetStyle.Normal.SetResourceObject(_emptySlot);
	}
	else
	{
		_slotBtns[slotIndex]->WidgetStyle.Normal.SetResourceObject(_itemImgs[itemId]);
	}

}

void UTFT_StoreUI::SetToDetailView0()
{
	UObject* image = _slotBtns[0]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Red Gem. Increase Attack Damage 50p.");
	FText price = FText::FromString("1,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView1()
{
	UObject* image = _slotBtns[1]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Blue Gem. Increase Max Mana 100p.");
	FText price = FText::FromString("1,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView2()
{
	UObject* image = _slotBtns[2]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Emerald Gem. Increase M/Health 100p & M/M 100p.");
	FText price = FText::FromString("2,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView3()
{
	UObject* image = _slotBtns[3]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Purple Potion. Get 1,000 EXP.");
	FText price = FText::FromString("2,500");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView4()
{
	UObject* image = _slotBtns[4]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("100 years old Wild Ginseng. Increase M/H 5,000p.");
	FText price = FText::FromString("80,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView5()
{
	UObject* image = _slotBtns[5]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Green Soup. Decrease M/H 1,000p & Increase A/D 300p");
	FText price = FText::FromString("3,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView6()
{
	UObject* image = _slotBtns[6]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Shield. Save your life once. Knight only.");
	FText price = FText::FromString("30,000");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView7()
{
	UObject* image = _slotBtns[7]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Arrow Head. Increase Attack Damage 20p. Archer only.");
	FText price = FText::FromString("300");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::SetToDetailView8()
{
	UObject* image = _slotBtns[8]->WidgetStyle.Normal.GetResourceObject();
	FText text = FText::FromString("Close...");
	FText price = FText::FromString("-");

	DetailViewImg->SetBrushResourceObject(image);
	Item_Information->SetText(text);
	Item_Price->SetText(price);
	_itemSlot = 0;
}

void UTFT_StoreUI::OnHovered(int32 slotIndex)
{
}
