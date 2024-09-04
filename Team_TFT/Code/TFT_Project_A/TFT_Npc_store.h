// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Creature.h"
#include "TFT_InteractionInterface.h"

#include "TFT_Npc_store.generated.h"

class UBoxComponent;
class UUserWidget;
class UTFT_StoreUI;
class ATFT_Item;

UCLASS()
class TFT_PROJECT_A_API ATFT_Npc_store : public ATFT_Creature, public ITFT_InteractionInterface
{
    GENERATED_BODY()

public:
    ATFT_Npc_store();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void Interact(ATFT_Item* item) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UUserWidget> StoreUIClass;

    UPROPERTY()
    UTFT_StoreUI* StoreUIInstance;

    class ITFT_InteractionInterface* _interface = nullptr;

private:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};