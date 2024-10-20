// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_GameModeBase.h"

#include "TFT_JobChoice.h"
#include "TFT_Player.h"
#include "TFT_Knight.h"
#include "TFT_Archer.h"
#include "TFT_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"

#include "TFT_TM_DH.h"
#include "TFT_TM_CG.h"
#include "TFT_TM_BJ.h"
#include "TFT_TM_IY.h"
#include "TFT_TestMannequin.h"


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

    static ConstructorHelpers::FClassFinder<ATFT_TM_DH> myDH
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_TM_DH_BP.TFT_TM_DH_BP_C'"));
    if (myDH.Succeeded())
    {
        _dh = myDH.Class;
    }

    static ConstructorHelpers::FClassFinder<ATFT_TM_CG> myCG
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_TM_CG_BP.TFT_TM_CG_BP_C'"));
    if (myCG.Succeeded())
    {
        _cg = myCG.Class;
    }

    static ConstructorHelpers::FClassFinder<ATFT_TM_BJ> myBJ
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_TM_BJ_BP.TFT_TM_BJ_BP_C'"));
    if (myBJ.Succeeded())
    {
        _bj = myBJ.Class;
    }

    static ConstructorHelpers::FClassFinder<ATFT_TM_IY> myIY
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_TM_IY_BP.TFT_TM_IY_BP_C'"));
    if (myIY.Succeeded())
    {
        _iy = myIY.Class;
    }

    static ConstructorHelpers::FClassFinder<ATFT_TestMannequin> myTestM
    (TEXT("/Script/Engine.Blueprint'/Game/BluePrint/Player/TFT_TestMannequin_BP.TFT_TestMannequin_BP_C'"));
    if (myTestM.Succeeded())
    {
        _testM = myTestM.Class;
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

        JobSelectionWidgetInstance->_DHSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerDH);
        JobSelectionWidgetInstance->_CGSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerCG);
        JobSelectionWidgetInstance->_BJSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerBJ);
        JobSelectionWidgetInstance->_IYSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerIY);
        
        JobSelectionWidgetInstance->_testSelected.AddDynamic(this, &ATFT_GameModeBase::SetPlayerTest);
    }

}

void ATFT_GameModeBase::BeginPlay()
{
	Super::BeginPlay();
    
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FInputModeUIOnly InputMode;
        InputMode.SetWidgetToFocus(JobSelectionWidgetInstance->TakeWidget());
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
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

    MouseLock();
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

    MouseLock();
}

void ATFT_GameModeBase::SetPlayerDH()
{
    DefaultPawnClass = _dh;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_TM_DH* player = GetWorld()->SpawnActor<ATFT_TM_DH>(_dh, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    MouseLock();
}

void ATFT_GameModeBase::SetPlayerCG()
{
    DefaultPawnClass = _cg;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_TM_CG* player = GetWorld()->SpawnActor<ATFT_TM_CG>(_cg, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    MouseLock();
}

void ATFT_GameModeBase::SetPlayerBJ()
{
    DefaultPawnClass = _bj;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_TM_BJ* player = GetWorld()->SpawnActor<ATFT_TM_BJ>(_bj, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    MouseLock();
}

void ATFT_GameModeBase::SetPlayerIY()
{
    DefaultPawnClass = _iy;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_TM_IY* player = GetWorld()->SpawnActor<ATFT_TM_IY>(_iy, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    MouseLock();
}

void ATFT_GameModeBase::SetPlayerTest()
{
    DefaultPawnClass = _testM;
    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    FRotator rotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

    ATFT_TestMannequin* player = GetWorld()->SpawnActor<ATFT_TestMannequin>(_testM, location, rotation);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorHiddenInGame(true);
    GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorEnableCollision(false);
    GetWorld()->GetFirstPlayerController()->UnPossess();
    GetWorld()->GetFirstPlayerController()->Possess(player);
    GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

    MouseLock();
}

void ATFT_GameModeBase::MouseLock()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);  // 입력 모드를 게임으로 전환
        PC->bShowMouseCursor = false;  // 마우스 커서를 숨김
    }
}
