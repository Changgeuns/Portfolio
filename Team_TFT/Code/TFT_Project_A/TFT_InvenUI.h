// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_InvenUI.generated.h"

class ATFT_Item;
class UTFT_InvenComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(SlotItem, ATFT_Item*, int itemIndex)
DECLARE_MULTICAST_DELEGATE(CloseInvenBtn);

UCLASS()
class TFT_PROJECT_A_API UTFT_InvenUI : public UUserWidget
{
	GENERATED_BODY()
	
public:


	virtual bool Initialize() override;

	UFUNCTION()
	void InvenOpenClose();

	UFUNCTION()
	void DropItem();

	UFUNCTION()
	void SetItemSlot(UTexture2D* texture, int32 slotIndex);

	UFUNCTION()
	void AddUiItem(ATFT_Item* item, int32 index);
	UFUNCTION()
	void SelectSlotItem(int32 index);

	UFUNCTION()
	void SetToDetailView0();
	UFUNCTION()
	void SetToDetailView1();
	UFUNCTION()
	void SetToDetailView2();
	UFUNCTION()
	void SetToDetailView3();
	UFUNCTION()
	void SetToDetailView4();
	UFUNCTION()
	void SetToDetailView5();
	UFUNCTION()
	void SetToDetailView6();
	UFUNCTION()
	void SetToDetailView7();
	UFUNCTION()
	void SetToDetailView8();


	void DeleteUIItem(int32 index);
	void UISetItemName(int32 index);
	void UISetItemMiniInfo(int32 index);
	void UISetItemExplanation(int32 index);
	void UIGold(int32 gold);

	CloseInvenBtn _CloseInvenBtn;
	SlotItem _SlotItemEvent;
private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Inven_Panel;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Inven_UniformGrid;

	UPROPERTY()
	bool bIsOpen = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UButton*> _slotBtns;
	TArray<class UTexture2D*> _itemImgs;

	UPROPERTY(meta = (BindWidget))
	class UImage* DetailViewImg;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Item_Information;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Inven_ItemMiniInfo;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Inven_ItemExplanation;


	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Inven_UIGold;

	UPROPERTY(meta = (BindWidget))
	UButton* Drop_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;

	UTexture2D* _emptySlot;
	FText _nullText = FText::FromString("");

private:
	TArray<ATFT_Item*> _UIsaveiteminfo;
	ATFT_Item* _this_Item;
	int32 this_Index = -1;
};
