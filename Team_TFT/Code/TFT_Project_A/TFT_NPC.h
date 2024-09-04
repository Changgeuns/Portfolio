// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Creature.h"
#include "TFT_InteractionInterface.h"

#include "TFT_NPC.generated.h"

class USphereComponent;


UCLASS()
class TFT_PROJECT_A_API ATFT_NPC : public ATFT_Creature, public ITFT_InteractionInterface
{
	GENERATED_BODY()
	
public:
	ATFT_NPC();

	virtual void SetMesh(FString path) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;




	UFUNCTION()
	void OnPlayerOverlapBegin
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnPlayerOverlapEnd
	(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USphereComponent* _area;

	bool _isOverlap = false;

	class ITFT_InteractionInterface* _interface = nullptr;
};
