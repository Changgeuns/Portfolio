// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TFT_StoreUI.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPurchaseDelegateOneParam, int32);


UCLASS()
class TFT_PROJECT_A_API UTFT_StoreUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void StoreOpenClose();

	UFUNCTION()
	void PurchaseItem();

	UFUNCTION()
	void SetItemSlot(int32 itemId, int32 slotIndex);

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

	UFUNCTION()
	void OnHovered(int32 slotIndex);

	FPurchaseDelegateOneParam _purchaseDelegateOneParam;

private:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Store_Panel;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* Store_UniformGrid;

	UPROPERTY()
	bool bIsOpen = false;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UButton*> _slotBtns;
	TArray<class UTexture2D*> _itemImgs;

	UPROPERTY()
	int32 _itemSlot;

	UPROPERTY(meta = (BindWidget))
	class UImage* DetailViewImg;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Item_Information;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Item_Price;

	UPROPERTY(meta = (BindWidget))
	UButton* Purchase_Button;
	UPROPERTY(meta = (BindWidget))
	UButton* Exit_Button;
	

	UTexture2D* _emptySlot;
	UTexture2D* _redGem;
	UTexture2D* _blueGem;
	UTexture2D* _emeraldGem;
	UTexture2D* _purplePotion;
	UTexture2D* _wildGinseng;
	UTexture2D* _greenSoup;
	UTexture2D* _shield;
	UTexture2D* _arrowHead;

};
