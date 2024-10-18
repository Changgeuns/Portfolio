// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFT_UIManager.generated.h"


class UUserWidget;
class UTFT_InvenUI;
class UTFT_TM_SkillUI;
class UTFT_Equipment_Window;
class UTFT_AggroUI;
class UUTFT_PartyHPWidget;

DECLARE_MULTICAST_DELEGATE(UIOpenEvent);

UENUM()
enum class UIType : int32
{
	CrossHair,
	Inventory,
	SkillUI,
	EquipmentUI,
	AggroUI,
	PartyHPUI,
};


UCLASS()
class TFT_PROJECT_A_API ATFT_UIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFT_UIManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void OpenWidget(UIType type);
	void CloseWidget(UIType type);
	void CloseAll();

	UFUNCTION()
	void OpenInvenUIA();
	UFUNCTION()
	void CloseInvenBtn();

	UFUNCTION()
	void OnOffEquipmentUIA();
	UFUNCTION()
	void CloseEquipmentUIA();

	void BindHPUpdateToAI(const TArray<class ATFT_TeamAI_Archer*>& ArcherAIs, const TArray<class ATFT_TeamAI_Knight*>& KnightAIs);  // AI 캐릭터들의 HP 업데이트 바인딩 함수

	void OnArcherHPChanged(float NewHPRatio, int32 Index);  
	void OnKnightHPChanged(float NewHPRatio, int32 Index);  

	UTFT_InvenUI* GetInvenUI() { return _invenWidget; }
	UUserWidget* GetCrossHair() { return _crossHair; }
	UTFT_TM_SkillUI* GetSkillUI() { return _skillUIWidget; }
	UTFT_Equipment_Window* GetEquipmentUI() { return _EquipmentWidget; }
	UTFT_AggroUI* GetAggroUI() { return _aggroUIWidget; }
	UUTFT_PartyHPWidget* GetPartyHPUI() { return _partyHPWidget; }

	UFUNCTION(BlueprintCallable)
	TArray<UUserWidget*> GetWidgets() { return _widgets; }

	UIOpenEvent _invenOpenEvent;
	UIOpenEvent _EquipmentOpenEvent;
	UIOpenEvent _EquipmentCloseResetEvent;

	void MouseUnLock(UIType type);
	void MouseLock(UIType type);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUserWidget*> _widgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UTFT_InvenUI* _invenWidget;

	bool _UIInvenarea = false;
	bool _UIEquipmentarea = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUserWidget* _crossHair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UTFT_TM_SkillUI* _skillUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UTFT_Equipment_Window* _EquipmentWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UTFT_AggroUI* _aggroUIWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	UUTFT_PartyHPWidget* _partyHPWidget;
};
