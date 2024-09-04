// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_JobChoice.h"
#include "Components/Button.h"

void UTFT_JobChoice::NativeConstruct()
{
	Super::NativeConstruct();

	if (UButton* KnightButton = Cast<UButton>(GetWidgetFromName(TEXT("KnightButton"))))
	{
		KnightButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnKnightButtonClicked);
	}

	if (UButton* ArcherButton = Cast<UButton>(GetWidgetFromName(TEXT("ArcherButton"))))
	{
		ArcherButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnArcherButtonClicked);
	}

}
void UTFT_JobChoice::OnKnightButtonClicked()
{

	_knightSelected.Broadcast();
	UE_LOG(LogTemp, Error, TEXT("Your Select : Knight"));

	HideUI();


}

void UTFT_JobChoice::OnArcherButtonClicked()
{
	_archerSelected.Broadcast();
	UE_LOG(LogTemp, Error, TEXT("Your Select : Archer"));

	HideUI();


}

void UTFT_JobChoice::HideUI()
{
	
	this->RemoveFromParent();
}


