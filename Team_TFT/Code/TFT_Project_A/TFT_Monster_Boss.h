#pragma once

#include "CoreMinimal.h"
#include "TFT_Monster.h"
#include "TFT_AggroComponent.h"
#include "TFT_TeamAI_Knight.h"
#include "TFT_TeamAI_Archer.h"
#include "TFT_Player.h"

#include "TFT_Monster_Boss.generated.h"

class ATFT_AreaDamage;

UCLASS()
class TFT_PROJECT_A_API ATFT_Monster_Boss : public ATFT_Monster
{
    GENERATED_BODY()

public:
    ATFT_Monster_Boss();

    virtual void PostInitializeComponents() override;
    virtual void BeginPlay() override;
    virtual void SetMesh(FString path) override;
    virtual void Attack_AI() override;

    virtual void AttackStart() override;

    UFUNCTION()
    void AttackHit_Boss();

    virtual void DropItem() override;

    virtual void DeathStart() override;

    UFUNCTION()
    void Boss_DeathEnd();

    UFUNCTION()
    void BossDisable();

    void UpdateBlackboardTarget();

    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
    UTFT_AggroComponent* AggroComponent;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Anim, meta = (AllowPrivateAccess = true))
    class UTFT_AnimInstance_Monster* _animInstance_Boss;

    float TotalDamageTaken;
    float TotalDamageFromPlayer;
    float TotalDamageFromKnight;
    float TotalDamageFromArcher;

    ATFT_Player* TargetPlayer = nullptr;
    ATFT_TeamAI_Knight* TargetKnight = nullptr;
    ATFT_TeamAI_Archer* TargetArcher = nullptr;
};
