#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TFT_AggroComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFT_PROJECT_A_API UTFT_AggroComponent : public UActorComponent
{
    GENERATED_BODY()

public:
   
    UTFT_AggroComponent();

    
    void AddDamage(float DamageAmount, AActor* DamagingActor);

   
    AActor* GetAggroTarget() const;

protected:
    virtual void BeginPlay() override;

private:
    void UpdateAggroTarget();

    float CurrentAggro; 
    float AggroThreshold; 
    
    UPROPERTY()
    AActor* AggroTarget; 

    
    UPROPERTY()
    TMap<AActor*, float> PlayerDamageMap;
};
