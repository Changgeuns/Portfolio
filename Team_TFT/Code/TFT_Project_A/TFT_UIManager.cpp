// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TFT_InvenUI.h"
#include "TFT_StoreUI.h"


ATFT_UIManager::ATFT_UIManager()
{
	
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> invenUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_InvenWidget_BP.TFT_InvenWidget_BP_C'"));
	if (invenUI.Succeeded())
	{
		auto temp = invenUI.Class;
		_invenWidget = CreateWidget<UTFT_InvenUI>(GetWorld(), temp);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> crossHair(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_CrossHair_BP.TFT_CrossHair_BP_C'"));

	if (crossHair.Succeeded())
	{
		_crossHair = CreateWidget<UUserWidget>(GetWorld(), crossHair.Class);
	}

	_widgets.Add(_crossHair);
	_widgets.Add(_invenWidget);
}


void ATFT_UIManager::BeginPlay()
{
	Super::BeginPlay();
	
	OpenWidget(UIType::Inventory);
	CloseWidget(UIType::Inventory);

	OpenWidget(UIType::CrossHair);

	_invenOpenEvent.AddUObject(this, &ATFT_UIManager::OpenInvenUIA);
	_invenWidget->_CloseInvenBtn.AddUObject(this, &ATFT_UIManager::CloseInvenBtn);
}

void ATFT_UIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_UIManager::OpenWidget(UIType type)
{

	int32 typeNum = (int32)type;
	if (_widgets.Num() <= typeNum)
		return;

	_widgets[typeNum]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	_widgets[typeNum]->AddToViewport(typeNum);
}

void ATFT_UIManager::CloseWidget(UIType type)
{

	int32 typeNum = (int32)type;
	if (_widgets.Num() <= typeNum)
		return;

	_widgets[typeNum]->SetVisibility(ESlateVisibility::Hidden);
	_widgets[typeNum]->RemoveFromViewport();
}

void ATFT_UIManager::CloseAll()
{
	for (auto widget : _widgets)
	{
		widget->SetVisibility(ESlateVisibility::Hidden);
		widget->RemoveFromViewport();
	}
}

void ATFT_UIManager::OpenInvenUIA()
{
	if (_UIarea == false)
	{
		UE_LOG(LogTemp, Log, TEXT("ainven : open"));
		_UIarea = true;
		OpenWidget(UIType::Inventory);
	}
	else if (_UIarea == true)
	{
		UE_LOG(LogTemp, Log, TEXT("inven : close"));
		_UIarea = false;
		CloseWidget(UIType::Inventory);
	}
}

void ATFT_UIManager::CloseInvenBtn()
{
	UE_LOG(LogTemp, Log, TEXT("inven : close"));
	_UIarea = false;
	CloseWidget(UIType::Inventory);
}




