// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TFT_InteractionInterface.generated.h"

class ATFT_Item;


UINTERFACE(MinimalAPI)
class UTFT_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class TFT_PROJECT_A_API ITFT_InteractionInterface
{
	GENERATED_BODY()


public:
	UFUNCTION()
	virtual void Interact(ATFT_Item* item) PURE_VIRTUAL(ITFT_InteractionInterface::Interact, ;);
};
