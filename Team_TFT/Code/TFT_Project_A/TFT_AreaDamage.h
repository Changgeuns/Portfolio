// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFT_AreaDamage.generated.h"

UCLASS()
class TFT_PROJECT_A_API ATFT_AreaDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ATFT_AreaDamage();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Lifetime = 5.0f;

private:
	void ApplyDamage();
	void OnLifetimeExpired();

	FTimerHandle LifetimeTimerHandle;
};
