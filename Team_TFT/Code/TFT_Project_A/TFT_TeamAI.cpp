// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_TeamAI.h"

#include "TFT_TeamAI_AIController.h"

ATFT_TeamAI::ATFT_TeamAI()
{
	PrimaryActorTick.bCanEverTick = true;

	APawn::AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ATFT_TeamAI::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ATFT_TeamAI::Attack_AI()
{
}
