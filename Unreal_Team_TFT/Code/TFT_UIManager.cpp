// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_UIManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TFT_InvenUI.h"
#include "TFT_StoreUI.h"
#include "TFT_TM_SkillUI.h"
#include "TFT_Equipment_Window.h"
#include "TFT_AggroUI.h"
#include "TFT_TeamAI_Archer.h"
#include "TFT_TeamAI_Knight.h"
#include "UTFT_PartyHPWidget.h"

#include "Kismet/GameplayStatics.h"


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

	static ConstructorHelpers::FClassFinder<UUserWidget> skillUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TM_UI/TFT_TM_SkillUI_BP.TFT_TM_SkillUI_BP_C'"));
	if (skillUI.Succeeded())
	{
		_skillUIWidget = CreateWidget<UTFT_TM_SkillUI>(GetWorld(), skillUI.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> EquipmentUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/CG_UI/UTFT_Equipment_BP.UTFT_Equipment_BP_C'"));
	if (EquipmentUI.Succeeded())
	{
		_EquipmentWidget = CreateWidget<UTFT_Equipment_Window>(GetWorld(), EquipmentUI.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> aggroUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_AggroWidget_BP.TFT_AggroWidget_BP_C'"));
	if (aggroUI.Succeeded())
	{
		_aggroUIWidget = CreateWidget<UTFT_AggroUI>(GetWorld(), aggroUI.Class);
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> partyHPUI(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/PartyHPWidget.PartyHPWidget_C'"));
	if (partyHPUI.Succeeded())
	{
		_partyHPWidget = CreateWidget<UUTFT_PartyHPWidget>(GetWorld(), partyHPUI.Class);
	}

	_widgets.Add(_crossHair);
	_widgets.Add(_invenWidget);
	_widgets.Add(_skillUIWidget);
	_widgets.Add(_EquipmentWidget);
	_widgets.Add(_aggroUIWidget);
	_widgets.Add(_partyHPWidget);
}


void ATFT_UIManager::BeginPlay()
{
	Super::BeginPlay();
	
	OpenWidget(UIType::Inventory);
	CloseWidget(UIType::Inventory);

	// OpenWidget(UIType::CrossHair);
	OpenWidget(UIType::SkillUI);

	OpenWidget(UIType::EquipmentUI);
	CloseWidget(UIType::EquipmentUI);

	// OpenWidget(UIType::PartyHPUI);

	_invenOpenEvent.AddUObject(this, &ATFT_UIManager::OpenInvenUIA);
	_invenWidget->_CloseInvenBtn.AddUObject(this, &ATFT_UIManager::CloseInvenBtn);
	_EquipmentOpenEvent.AddUObject(this, &ATFT_UIManager::OnOffEquipmentUIA);
	_EquipmentWidget->_CloseEquipmentBtn.AddUObject(this, &ATFT_UIManager::CloseEquipmentUIA);

	TArray<AActor*> FoundArchers;
	TArray<AActor*> FoundKnights;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFT_TeamAI_Archer::StaticClass(), FoundArchers);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFT_TeamAI_Knight::StaticClass(), FoundKnights);

	TArray<ATFT_TeamAI_Archer*> ArcherAIs;
	TArray<ATFT_TeamAI_Knight*> KnightAIs;

	for (AActor* Actor : FoundArchers)
	{
		ArcherAIs.Add(Cast<ATFT_TeamAI_Archer>(Actor));
	}
	for (AActor* Actor : FoundKnights)
	{
		KnightAIs.Add(Cast<ATFT_TeamAI_Knight>(Actor));
	}

	BindHPUpdateToAI(ArcherAIs, KnightAIs);

}

void ATFT_UIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_UIManager::OpenWidget(UIType type)
{
	int32 typeNum = (int32)type;
	if (_widgets.Num() <= typeNum) return;

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
	if (_UIInvenarea == false)
	{
		UE_LOG(LogTemp, Log, TEXT("ainven : open"));
		_UIInvenarea = true;
		OpenWidget(UIType::Inventory);
		MouseUnLock(UIType::Inventory);
	}
	else if (_UIInvenarea == true)
	{
		UE_LOG(LogTemp, Log, TEXT("inven : close"));
		_UIInvenarea = false;
		CloseWidget(UIType::Inventory);
		MouseLock(UIType::Inventory);
	}
}

void ATFT_UIManager::CloseInvenBtn()
{
	UE_LOG(LogTemp, Log, TEXT("inven : close"));
	_UIInvenarea = false;
	CloseWidget(UIType::Inventory);
	MouseLock(UIType::Inventory);
}

void ATFT_UIManager::OnOffEquipmentUIA()
{
	if (_UIEquipmentarea == false)
	{
		UE_LOG(LogTemp, Log, TEXT("Equipment : open"));
		_UIEquipmentarea = true;
		OpenWidget(UIType::EquipmentUI);
		MouseUnLock(UIType::EquipmentUI);
	}
	else if (_UIEquipmentarea == true)
	{
		UE_LOG(LogTemp, Log, TEXT("Equipment : close"));
		_UIEquipmentarea = false;
		_EquipmentCloseResetEvent.Broadcast();
		CloseWidget(UIType::EquipmentUI);
		MouseLock(UIType::EquipmentUI);
	}
}

void ATFT_UIManager::CloseEquipmentUIA()
{
	UE_LOG(LogTemp, Log, TEXT("Equipment : close"));
	_UIEquipmentarea = false;
	_EquipmentCloseResetEvent.Broadcast();
	CloseWidget(UIType::EquipmentUI);
	MouseLock(UIType::EquipmentUI);
}

void ATFT_UIManager::BindHPUpdateToAI(const TArray<class ATFT_TeamAI_Archer*>& ArcherAIs, const TArray<class ATFT_TeamAI_Knight*>& KnightAIs)
{
	for (int32 i = 0; i < ArcherAIs.Num(); ++i)
	{
		if (ArcherAIs[i] && ArcherAIs[i]->_statCom)
		{
			float initialHPRatio = ArcherAIs[i]->_statCom->HpRatio();
			OnArcherHPChanged(initialHPRatio, i);
			ArcherAIs[i]->_statCom->OnHPChanged.AddUObject(this, &ATFT_UIManager::OnArcherHPChanged, i);
		}
	}

	for (int32 i = 0; i < KnightAIs.Num(); ++i)
	{
		if (KnightAIs[i] && KnightAIs[i]->_statCom)
		{
			float initialHPRatio = KnightAIs[i]->_statCom->HpRatio();
			OnKnightHPChanged(initialHPRatio, i);
			KnightAIs[i]->_statCom->OnHPChanged.AddUObject(this, &ATFT_UIManager::OnKnightHPChanged, i);
		}
	}
}

void ATFT_UIManager::OnArcherHPChanged(float NewHPRatio, int32 Index)
{
	if (_partyHPWidget)
	{
		_partyHPWidget->UpdateArcherHPBar(Index, NewHPRatio);
	}
}

void ATFT_UIManager::OnKnightHPChanged(float NewHPRatio, int32 Index)
{
	if (_partyHPWidget)
	{
		_partyHPWidget->UpdateKnightHPBar(Index, NewHPRatio);
	}
}

void ATFT_UIManager::MouseUnLock(UIType type)
{

	int32 typeNum = (int32)type;
	if (_widgets.Num() <= typeNum)
		return;

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(_widgets[typeNum]->TakeWidget());  // 포커스를 해당 UI로 설정
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);  // 마우스 잠금 해제
		PC->SetInputMode(InputMode);  // 입력 모드 변경
		PC->bShowMouseCursor = true;  // 마우스 커서 표시
	}
}

void ATFT_UIManager::MouseLock(UIType type)
{
	int32 typeNum = (int32)type;
	if (_widgets.Num() <= typeNum)
		return;

	// 마우스를 다시 게임 모드로 전환 (UI가 닫힌 후)
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);  // 입력 모드를 게임으로 전환
		PC->bShowMouseCursor = false;  // 마우스 커서를 숨김
	}
}





