// Fill out your copyright notice in the Description page of Project Settings.

#include "TFT_Npc_store.h"
#include "Components/BoxComponent.h"
#include "TFT_StoreUI.h"
#include "TFT_Player.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"

ATFT_Npc_store::ATFT_Npc_store()
{
    PrimaryActorTick.bCanEverTick = true;


    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetBoxExtent(FVector(200.f, 200.f, 200.f));
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

  
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATFT_Npc_store::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ATFT_Npc_store::OnOverlapEnd);

    _storeCom = CreateDefaultSubobject<UTFT_StoreComponent>(TEXT("Store_Com"));
}

void ATFT_Npc_store::BeginPlay()
{
    Super::BeginPlay();
}

void ATFT_Npc_store::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATFT_Npc_store::Interact(ATFT_Item* item)
{
    UE_LOG(LogTemp, Log, TEXT("NPC Interact With Player!"));
    if (_interface != nullptr)
    {
        _interface->Interact(item);
    }
}

void ATFT_Npc_store::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ATFT_Player* player = Cast<ATFT_Player>(OtherActor);


    if (player != nullptr)
    {
        _interface = Cast<ITFT_InteractionInterface>(OtherActor);
        _storeCom->GetStoreUI()->StoreOpenClose();
    }
}

void ATFT_Npc_store::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ATFT_Player* player = Cast<ATFT_Player>(OtherActor);


    if (player != nullptr)
    {
        _interface = nullptr;
        _storeCom->GetStoreUI()->StoreOpenClose();
    }
}