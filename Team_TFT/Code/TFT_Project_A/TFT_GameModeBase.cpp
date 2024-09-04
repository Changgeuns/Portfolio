// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_GameModeBase.h"

#include "TFT_JobChoice.h"
#include "TFT_Player.h"
#include "TFT_Knight.h"
#include "TFT_Archer.h"
#include "TFT_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"

ATFT_GameModeBase::ATFT_GameModeBase()
{
	static ConstructorHelpers::FClassFinder<ATFT_Knight> myKnight
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_Knight_BP.TFT_Knight_BP_C'"));
	if (myKnight.Succeeded())
	{
		_knight = myKnight.Class;
	}

    static ConstructorHelpers::FClassFinder<ATFT_Archer> myArcher
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_Archer_BP.TFT_Archer_BP_C'"));
    if (myArcher.Succeeded())
    {
        _archer = myArcher.Class;
    }



    if (UClass* JobSelectionWidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_Job_BP.TFT_Job_BP_C'")))
    {
        JobSelectionWidgetInstance = CreateWidget<UTFT_JobChoice>(GetWorld(), JobSelectionWidgetClass);
        if (JobSelectionWidgetInstance)
        {
            JobSelectionWidgetInstance->AddToViewport(9999); 
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create JobSelectionWidgetInstance"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JobSelectionWidgetClass"));
    }
}

void ATFT_GameModeBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (JobSelectionWidgetInstance->IsValidLowLevel())
    {
        JobSelectionWidgetInstance->_knightSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerKnight);
        JobSelectionWidgetInstance->_archerSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerArcher);
    }

}

void ATFT_GameModeBase::BeginPlay()
{
	Super::BeginPlay();


}

void ATFT_GameModeBase::SetPlayerKnight()
{
    DefaultPawnClass = _knight;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_Knight* player = GetWorld()->SpawnActor<ATFT_Knight>(_knight, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    SoundManager->Play("Knight_Choice", location);
}

void ATFT_GameModeBase::SetPlayerArcher()
{
    DefaultPawnClass = _archer;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_Archer* player = GetWorld()->SpawnActor<ATFT_Archer>(_archer, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    SoundManager->Play("Archer_Choice", location);
}
