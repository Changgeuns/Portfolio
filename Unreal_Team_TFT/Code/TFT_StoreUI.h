// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_StoreUI.generated.h"

class UTextBlock;
class ATFT_Item;

DECLARE_MULTICAST_DELEGATE_OneParam(FPurchaseDelegateOneParam, int32)
DECLARE_MULTICAST_DELEGATE_TwoParams(ItemBuyEvent, ATFT_Item*, int32 index)

UCLASS()
class TFT_PROJECT_A_API UTFT_StoreUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
	void StoreOpenClose();

	UFUNCTION()
	void PurchaseItem();

	UFUNCTION()
	void SelectSlotStoreItem(int32 index);

	UFUNCTION()
	void SetItemSlot(UTexture2D* texture, int32 slotIndex);
	UFUNCTION()
	void SetStoreItem(ATFT_Item* items, int32 index);


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
	


	void UISetItemName(int32 index);
	void UISetItemMiniInfo(int32 index);
	void UISetItemPrice(int32 index);

	bool GetOpenCheke() { return bIsOpen; }

	FPurchaseDelegateOneParam _purchaseDelegateOneParam;
	ItemBuyEvent _ItemBuy;
private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Store_Panel;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Store_UniformGrid;

	UPROPERTY()
	bool bIsOpen = true;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UButton*> _slotBtns;
	TArray<class UTexture2D*> _itemImgs;

	UPROPERTY()
	int32 _itemSlot;

	UPROPERTY(meta = (BindWidget))
	class UImage* DetailViewImg;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Information;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_miniInfo;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Price;

	UPROPERTY(meta = (BindWidget))
	UButton* Purchase_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;

	UTexture2D* _emptySlot;
	FText _nullText = FText::FromString("");
	
private:
	TArray<ATFT_Item*> _Storesaveiteminfo;
	ATFT_Item* _this_Item;
	int32 this_Index = -1;
	
};
