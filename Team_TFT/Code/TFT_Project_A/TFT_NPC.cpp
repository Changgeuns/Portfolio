// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_NPC.h"
#include "Components/SphereComponent.h"
#include "TFT_StoreUI.h"
#include "TFT_Player.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"


ATFT_NPC::ATFT_NPC()
{
	_meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));

	SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Skins/Rogue/Meshes/Sparrow_Rogue.Sparrow_Rogue'");

	_area = CreateDefaultSubobject<USphereComponent>(TEXT("Area"));

	_area->SetupAttachment(RootComponent);
	_area->SetCollisionProfileName(TEXT("Trigger"));
	_area->SetSphereRadius(100.0f);

	_storeCom = CreateDefaultSubobject<UTFT_StoreComponent>(TEXT("Store_Com"));
}

void ATFT_NPC::SetMesh(FString path)
{
	_meshCom->SetMesh(path);
}

void ATFT_NPC::BeginPlay()
{
	Super::BeginPlay();
}

void ATFT_NPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_area->OnComponentBeginOverlap.AddDynamic(this, &ATFT_NPC::OnPlayerOverlapBegin);
	_area->OnComponentEndOverlap.AddDynamic(this, &ATFT_NPC::OnPlayerOverlapEnd);
}



void ATFT_NPC::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto player = Cast<ATFT_Player>(OtherActor);

	if (player != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("NPC Collisions with %s."), *player->GetName());

		_interface = Cast<ITFT_InteractionInterface>(OtherActor);
		_isOverlap = true;
		_storeCom->GetStoreUI()->StoreOpenClose();
	}
}

void ATFT_NPC::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto player = Cast<ATFT_Player>(OtherActor);
	if (player != nullptr)
	{
		_interface = nullptr;
		_isOverlap = false;
		_storeCom->GetStoreUI()->StoreOpenClose();
	}
}
