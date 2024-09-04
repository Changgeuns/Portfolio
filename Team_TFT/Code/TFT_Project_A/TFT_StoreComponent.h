// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TFT_StoreComponent.generated.h"

class UTFT_StoreUI;
class UImage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TFT_PROJECT_A_API UTFT_StoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UTFT_StoreComponent();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PurchaseItem(int32 itemSlot);

	UTFT_StoreUI* GetStoreUI() { return _storeWidget; }

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> _storeWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Store, meta = (AllowPrivateAccess = true))
	UTFT_StoreUI* _storeWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TArray<class ATFT_Item*> _items;
	UPROPERTY()
	TSubclassOf<class ATFT_Item> _itemClass;
	int32 _storeMaxSize = 9;
	UPROPERTY()
	ATFT_Item* _item;
};
