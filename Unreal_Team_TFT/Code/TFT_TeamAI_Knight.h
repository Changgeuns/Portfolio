// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFT_TeamAI.h"
#include "TFT_TeamAI_Knight.generated.h"


UCLASS()
class TFT_PROJECT_A_API ATFT_TeamAI_Knight : public ATFT_TeamAI
{
	GENERATED_BODY()
	
public:
	ATFT_TeamAI_Knight();

	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	virtual void Init() override;

	virtual void SetMesh(FString path) override;

	virtual void Attack_AI() override;

	virtual void AttackStart() override;

	virtual void AttackHit() override;

	virtual void DeathStart() override;

	virtual void Disable() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = true))
	class UTFT_AnimInstance_Knight* _animInstance_Knight;

	int32 Index;
};
