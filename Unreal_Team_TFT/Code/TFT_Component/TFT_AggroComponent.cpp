#include "TFT_AggroComponent.h"

#include "TFT_Knight.h"
#include "TFT_Archer.h"
#include "TFT_TeamAI_Knight.h"
#include "TFT_TeamAI_Archer.h"

UTFT_AggroComponent::UTFT_AggroComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    CurrentAggro = 0.0f;
    AggroThreshold = 100.0f;
    AggroTarget = nullptr;
}

void UTFT_AggroComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTFT_AggroComponent::AddDamage(float DamageAmount, AActor* DamagingActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Damage Added: %f"), DamageAmount);


    if (DamagingActor)
    {
        if (PlayerDamageMap.Contains(DamagingActor))
        {
            PlayerDamageMap[DamagingActor] += DamageAmount;
        }
        else
        {
            PlayerDamageMap.Add(DamagingActor, DamageAmount);
        }

       
    }
}


AActor* UTFT_AggroComponent::GetAggroTarget()
{
    UpdateAggroTarget();
    return AggroTarget;
}

float UTFT_AggroComponent::GetTotalDamage(AActor* DamagingActor)
{
    if (DamagingActor == nullptr) return -1; 

    float damage = PlayerDamageMap[DamagingActor];

    return damage;
}

void UTFT_AggroComponent::AggroList()
{
    if (PlayerDamageMap.Num() <= 0) return;

    FString DebugMessage;
    FColor MessageColor = FColor::Green;
    
    int32 MessageKey = 0;

    for (auto all : PlayerDamageMap)
    {
        MessageKey++;
        AActor* enemy = all.Key;
        FString enemyName = enemy->GetName();
        float enemyDamage = all.Value;

        DebugMessage = FString::Printf(TEXT("%s 's Total Damage : %f"), *enemyName, enemyDamage);
      
        if (enemyDamage >= maxValue)
        {
            maxValue = enemyDamage;
            MessageColor = FColor::Red;
        }
        else
        {
            MessageColor = FColor::Green;
        }

        const float TimeToDisplay = 500.0f;

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(MessageKey, TimeToDisplay, MessageColor, DebugMessage);
        }

    }


}

void UTFT_AggroComponent::UpdateAggroTarget()
{
    AggroTarget = nullptr;
    if (PlayerDamageMap.Num() <= 0)
    {
        AggroTarget = nullptr;
        return;
    }

    AActor* NewAggroTarget = nullptr;
    float MaxDamage = 0.0f;

    for (const auto& Elem : PlayerDamageMap)
    {
        if (Elem.Value > MaxDamage)
        {
            MaxDamage = Elem.Value;
            NewAggroTarget = Elem.Key;
        }
    }

    if (NewAggroTarget != AggroTarget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Aggro Target Updated: %s"), *NewAggroTarget->GetName());
        AggroTarget = NewAggroTarget;
    }
}
