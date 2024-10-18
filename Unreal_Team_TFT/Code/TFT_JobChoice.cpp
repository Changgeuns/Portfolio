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

	if (UButton* DHButton = Cast<UButton>(GetWidgetFromName(TEXT("DH_Button"))))
	{
		DHButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnDHButtonClicked);
	}

	if (UButton* CGButton = Cast<UButton>(GetWidgetFromName(TEXT("CG_Button"))))
	{
		CGButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnCGButtonClicked);
	}

	if (UButton* BJButton = Cast<UButton>(GetWidgetFromName(TEXT("BJ_Button"))))
	{
		BJButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnBJButtonClicked);
	}

	if (UButton* IYButton = Cast<UButton>(GetWidgetFromName(TEXT("IY_Button"))))
	{
		IYButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnIYButtonClicked);
	}

	if (UButton* TestButton = Cast<UButton>(GetWidgetFromName(TEXT("TEST_Button"))))
	{
		TestButton->OnClicked.AddDynamic(this, &UTFT_JobChoice::OnTestButtonClicked);
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

void UTFT_JobChoice::OnDHButtonClicked()
{
	_DHSelected.Broadcast();

	HideUI();
}

void UTFT_JobChoice::OnCGButtonClicked()
{
	_CGSelected.Broadcast();

	HideUI();
}

void UTFT_JobChoice::OnBJButtonClicked()
{
	_BJSelected.Broadcast();

	HideUI();
}

void UTFT_JobChoice::OnIYButtonClicked()
{
	_IYSelected.Broadcast();

	HideUI();
}

void UTFT_JobChoice::OnTestButtonClicked()
{
	_testSelected.Broadcast();

	HideUI();
}

void UTFT_JobChoice::HideUI()
{
	this->RemoveFromParent();
}


