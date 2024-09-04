// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TFT_StatComponent.h"


#include "TFT_GameInstance.generated.h"

class ATFT_UIManager;
class ATFT_Effect_Manager;
class ATFT_SoundManager;



#define UIMANAGER Cast<UTFT_GameInstance>(GetGameInstance())->GetUIManager()
#define EffectManager Cast<UTFT_GameInstance>(GetGameInstance())->GetEffectManager()
#define SoundManager Cast<UTFT_GameInstance>(GetGameInstance())->GetSoundManager()


UCLASS()
class TFT_PROJECT_A_API UTFT_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTFT_GameInstance();

	virtual void Init() override;

	FTFT_StatData* GetStatDataByLevel(int32 level);

	ATFT_UIManager* GetUIManager() { return _uiManager; }
	ATFT_Effect_Manager* GetEffectManager() { return _effectManager; }
	ATFT_SoundManager* GetSoundManager() { return _soundManager; }

private:

	UPROPERTY()
	class UDataTable* _statTable;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	ATFT_UIManager* _uiManager;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	ATFT_Effect_Manager* _effectManager;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	ATFT_SoundManager* _soundManager;
};
