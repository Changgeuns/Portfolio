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
	(TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Item/Test_item.Test_item_C'"));
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
			_storeWidget->_purchaseDelegateOneParam.AddUObject(this, &UTFT_StoreComponent::PurchaseItem);
			_storeWidget->AddToViewport();
		}
	}

	_item = GetWorld()->SpawnActor<ATFT_Item>(_itemClass, FVector::ZeroVector, FRotator::ZeroRotator);

	_items[0] = _item;
}



void UTFT_StoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTFT_StoreComponent::PurchaseItem(int32 itemSlot)
{
	auto npc = Cast<ATFT_Npc_store>(GetOwner());
	if (npc != nullptr)
	{
		npc->Interact(_items[itemSlot]);
	}
}

