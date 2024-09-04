// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_Player.h"
#include "TFT_Archer.generated.h"



UCLASS()
class TFT_PROJECT_A_API ATFT_Archer : public ATFT_Player
{
	GENERATED_BODY()
	
public:
	ATFT_Archer();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void SetMesh(FString path) override;

	virtual void AttackStart() override;

	UFUNCTION()
	void AttackHit_ADC();

	virtual void DeathStart() override;

	virtual void Disable() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATFT_Projectile> _projectileClass;
};
