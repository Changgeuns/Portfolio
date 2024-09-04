#include "TFT_AggroComponent.h"

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

        UpdateAggroTarget();
    }
}

AActor* UTFT_AggroComponent::GetAggroTarget() const
{
    return AggroTarget;
}

void UTFT_AggroComponent::UpdateAggroTarget()
{
    if (PlayerDamageMap.Num() == 0)
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
