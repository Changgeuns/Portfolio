// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_StoreComponent.h"

#include "Blueprint/UserWidget.h"
#include "TFT_Npc_store.h"
#include "TFT_StoreUI.h"
#include "TFT_Item.h"


UTFT_StoreComponent::UTFT_StoreComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> storeWidgetClass
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_StoreWidget_BP.TFT_StoreWidget_BP_C'"));
	if (storeWidgetClass.Succeeded())
	{
		_storeWidgetClass = storeWidgetClass.Class;
	}
	
	_items.SetNum(_storeMaxSize);

	static ConstructorHelpers::FClassFinder<ATFT_Item> item
	(TEXT("/Script/CoreUObject.Class'/Script/TFT_Project_A.TFT_Item'"));
	if (item.Succeeded())
	{
		_itemClass = item.Class;		
	}
}



void UTFT_StoreComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(_storeWidgetClass))
	{
		_storeWidget = Cast<UTFT_StoreUI>(CreateWidget(GetWorld(), _storeWidgetClass));
	
		if (IsValid(_storeWidget))
		{
			_storeWidget->_ItemBuy.AddUObject(this, &UTFT_StoreComponent::PurchaseItem);
			_storeWidget->AddToViewport();
		}
	}

	SetStoreItem(1);
	SetStoreItem(3);
	SetStoreItem(2);
	SetStoreItem(10);
	SetStoreItem(20);



}



void UTFT_StoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTFT_StoreComponent::PurchaseItem(ATFT_Item* item, int32 index)
{
	auto npc = Cast<ATFT_Npc_store>(GetOwner());
	if (npc != nullptr)
	{
		npc->Interact(item);
	}
}

void UTFT_StoreComponent::SetStoreItem(int32 lineNum)
{

	ATFT_Item* NewItem = GetWorld()->SpawnActor<ATFT_Item>(_itemClass, FVector::ZeroVector, FRotator::ZeroRotator);

	if (NewItem)
	{
		NewItem->SetItemid(lineNum);  

		for (int32 i = 0; i < _storeMaxSize; ++i)
		{
			if (_items.IsValidIndex(i) && _items[i] == nullptr)
			{
				_items[i] = NewItem;  
				_storeWidget->SetStoreItem(NewItem, i); 
				NewItem->Disable();
				return;
			}
		}
	}
}

