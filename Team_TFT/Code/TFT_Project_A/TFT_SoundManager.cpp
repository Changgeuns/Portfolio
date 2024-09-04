// Fill out your copyright notice in the Description page of Project Settings.


#include "TFT_SoundManager.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


ATFT_SoundManager::ATFT_SoundManager()
{

	PrimaryActorTick.bCanEverTick = false;

	CreateSoundCue("Knight_Choice", "/Script/Engine.SoundCue'/Game/ParagonTerra/Audio/Cues/Terra_Ability_E_Engage.Terra_Ability_E_Engage'");
	CreateSoundCue("Archer_Choice", "/Script/Engine.SoundCue'/Game/ParagonSparrow/Audio/Cues/Sparrow_DraftSelect.Sparrow_DraftSelect'");
	CreateSoundCue("Knight_Swing", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Long_And_Large/TFT_Knight_Swing_swing_large_metal_09_Cue.TFT_Knight_Swing_swing_large_metal_09_Cue'");
	CreateSoundCue("Archer_Shoot", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Short_And_Small/TFT_Archer_shoot_swing_small_wood_05_Cue.TFT_Archer_shoot_swing_small_wood_05_Cue'");
	CreateSoundCue("Monster_Normal_Swing", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Short_And_Small/TFT_Normal_Swing_swing_small_wood_10_Cue1.TFT_Normal_Swing_swing_small_wood_10_Cue1'");
	CreateSoundCue("Monster_Boss_Swing", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Long_And_Large/TFT_Boss_Swing_swing_large_other_00_Cue1.TFT_Boss_Swing_swing_large_other_00_Cue1'");
	CreateSoundCue("TeamAI_Knight_Swing", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Long_And_Large/TFT_AIKnight_Swing_swing_large_metal_09_Cue.TFT_AIKnight_Swing_swing_large_metal_09_Cue'");
	CreateSoundCue("TeamAI_Archer_Shoot", "/Script/Engine.SoundCue'/Game/Blade_Swings_And_Hits/CUES/Swings/Short_And_Small/TFT_AIArcher_shoot_swing_small_wood_05_Cue.TFT_AIArcher_shoot_swing_small_wood_05_Cue'");
	CreateSoundCue("Knight_Death", "/Script/Engine.SoundCue'/Game/ParagonTerra/Audio/Cues/Terra_Effort_Death.Terra_Effort_Death'");
	CreateSoundCue("Archer_Death", "/Script/Engine.SoundCue'/Game/ParagonSparrow/Audio/Cues/Sparrow_Effort_Death.Sparrow_Effort_Death'");
	CreateSoundCue("TeamAI_Knight_Death", "/Script/Engine.SoundCue'/Game/ParagonTerra/Audio/Cues/TFT_TeamAI_Terra_Effort_Death1.TFT_TeamAI_Terra_Effort_Death1'");
	CreateSoundCue("TeamAI_Archer_Death", "/Script/Engine.SoundCue'/Game/ParagonSparrow/Audio/Cues/TFT_TeamAI_Sparrow_Effort_Death1.TFT_TeamAI_Sparrow_Effort_Death1'");
	CreateSoundCue("Monster_Normal_Death", "/Script/Engine.SoundCue'/Game/ParagonGrux/Characters/Heroes/Grux/Sounds/SoundCues/TFT_Normal_Grux_Effort_Death.TFT_Normal_Grux_Effort_Death'");
	CreateSoundCue("Monster_Boss_Death", "/Script/Engine.SoundCue'/Game/ParagonGrux/Characters/Heroes/Grux/Sounds/SoundCues/Grux_Death_TFT.Grux_Death_TFT'");

}

void ATFT_SoundManager::CreateSoundCue(FString keyName, FString path)
{
	ConstructorHelpers::FObjectFinder<USoundCue> sound(*path);
	if (sound.Succeeded())
	{
		USoundCue* soundCue = sound.Object;
		_table.Add(keyName, soundCue);
	}
}


void ATFT_SoundManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFT_SoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFT_SoundManager::Play(FString keyName, FVector playLocation, FRotator playRotator)
{
	if (_table.Contains(keyName) == false) return;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), _table[keyName], playLocation, playRotator);
}

