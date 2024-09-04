// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_InvenComponent.h"

#include "TFT_Item.h"
#include "TFT_InvenUI.h"

#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"


UTFT_InvenComponent::UTFT_InvenComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	_items.SetNum(_inventoryMaxSize); 
	
}



void UTFT_InvenComponent::BeginPlay()
{
	Super::BeginPlay();


}



void UTFT_InvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UTFT_InvenComponent::AddItem(ATFT_Item* item)
{
	if (item->GetItemType() == "gold")
	{
		UE_LOG(LogTemp, Log, TEXT("%d gold Get~too ~"), item->GetItemGold());

		AddPlayerGold(item->GetItemGold());
		item->Disable();

		return;
	}
	else
	{
		for (int32 i = 0; i < _inventoryMaxSize; ++i)
		{
			if (_items.IsValidIndex(i) && _items[i] == nullptr)
			{
				_items[i] = item;
				UE_LOG(LogTemp, Log, TEXT("Added item to inventory at index: %d"), i);
				_itemAddedEvent.Broadcast(item, i);
				item->Disable();
				return;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full, unable to add item."));
	}

}



void UTFT_InvenComponent::DropItem(int32 index)
{
	UE_LOG(LogTemp, Log, TEXT("Item Drop"));


	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetOwner()->GetActorLocation();
	FVector itemPos = playerPos + FVector(X, Y, 0.0f);
	_items[index]->SetItemPos(itemPos);

	ATFT_Item* itemToRemove = _items[index];
	_items[index] = nullptr;
}

void UTFT_InvenComponent::SlectItemUI(int32 index)
{
	_itemSlectEvent.Broadcast(_items[index], index);
}

void UTFT_InvenComponent::AddPlayerGold(int32 gold)
{
	_playerGold += gold;
	_GoldChangeEvnet.Broadcast(_playerGold);
}
