#include "TFT_Monster_TB_CG.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "TFT_HpBar.h"
#include "TFT_AnimInstance_Monster.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "TFT_Monster_AIController.h"
#include "TFT_BossAI_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_AggroComponent.h"
#include "TFT_TeamAI_Knight.h"
#include "TFT_TeamAI_Archer.h"
#include "TFT_Player.h"

#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"
#include "TFT_Effect_Manager.h"
#include "TFT_UIManager.h"

#include "TFT_AggroUI.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Kismet/GameplayStatics.h"

ATFT_Monster_TB_CG::ATFT_Monster_TB_CG()
{
    _meshCom = CreateDefaultSubobject<UTFT_MeshComponent>(TEXT("Mesh_Com"));
    _invenCom = CreateDefaultSubobject<UTFT_InvenComponent>(TEXT("Inven_Com"));

    SetMesh("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Skins/Tier_2/Grux_Beetle_Molten/Meshes/GruxMolten.GruxMolten'");

    static ConstructorHelpers::FClassFinder<UUserWidget> HpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/TFT_HpBar_Boss_BP.TFT_HpBar_Boss_BP_C'"));
    if (HpBar.Succeeded())
    {
        HpBarWidgetClass = HpBar.Class;
    }

    AggroComponent = CreateDefaultSubobject<UTFT_AggroComponent>(TEXT("AggroComponent"));

    TotalDamageTaken = 0.0f;
    TotalDamageFromPlayer = 0.0f;
    TotalDamageFromKnight = 0.0f;
    TotalDamageFromArcher = 0.0f;

    _possessionExp = 100;

    WeaponCollisionCapsule_R = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollisionCapsule_R"));
    WeaponCollisionCapsule_R->SetupAttachment(GetMesh(), TEXT("weapon_r"));

    WeaponCollisionCapsule_L = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollisionCapsule_L"));
    WeaponCollisionCapsule_L->SetupAttachment(GetMesh(), TEXT("weapon_l"));

    WeaponCollisionCapsule_R->SetCapsuleRadius(10.f);
    WeaponCollisionCapsule_R->SetCapsuleHalfHeight(30.f);

    WeaponCollisionCapsule_L->SetCapsuleRadius(10.f);
    WeaponCollisionCapsule_L->SetCapsuleHalfHeight(30.f);
}

void ATFT_Monster_TB_CG::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    _animInstance_Boss = Cast<UTFT_AnimInstance_Monster>(GetMesh()->GetAnimInstance());

    if (_animInstance_Boss->IsValidLowLevel())
    {
        _animInstance_Boss->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
        _animInstance_Boss->_attackStartDelegate.AddUObject(this, &ATFT_Monster_TB_CG::AttackStart);
        _animInstance_Boss->_attackHitDelegate.AddUObject(this, &ATFT_Monster_TB_CG::AttackHit_Boss);
        _animInstance_Boss->_deathStartDelegate.AddUObject(this, &ATFT_Monster_TB_CG::DeathStart);
        _animInstance_Boss->_bossDeathEndDelegate.AddUObject(this, &ATFT_Monster_TB_CG::Boss_DeathEnd);
        _animInstance_Boss->_deathEndDelegate.AddUObject(this, &ATFT_Monster_TB_CG::BossDisable);
    }

    if (HpBarWidgetClass)
    {
        HpBarWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HpBarWidgetClass);
        if (HpBarWidgetInstance)
        {
            HpBarWidgetInstance->AddToViewport();
        }
    }

    if (HpBarWidgetInstance)
    {
        UTFT_HpBar* HpBar = Cast<UTFT_HpBar>(HpBarWidgetInstance);
        if (HpBar)
        {
            _statCom->_hpChangedDelegate.AddUObject(HpBar, &UTFT_HpBar::SetHpBarValue);
        }
    }
}

void ATFT_Monster_TB_CG::BeginPlay()
{
    Super::BeginPlay();

    if (AggroComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("AggroComponent is valid."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AggroComponent is not initialized!"));
    }

    _statCom->SetLevelAndInit(101);
    UpdateBlackboardTarget();
}

void ATFT_Monster_TB_CG::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (Player)
    {
        float Distance = FVector::Dist(Player->GetActorLocation(), GetActorLocation());

        if (HpBarWidgetInstance)
        {
            if (Distance <= 1500.0f)
            {
                HpBarWidgetInstance->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                HpBarWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}

void ATFT_Monster_TB_CG::SetMesh(FString path)
{
    _meshCom->SetMesh(path);
}

void ATFT_Monster_TB_CG::Attack_AI()
{
    Super::Attack_AI();

    if (_isAttacking == false && _animInstance_Boss != nullptr)
    {
        _animInstance_Boss->PlayAttackMontage();
        _isAttacking = true;

        _curAttackIndex %= 3;
        _curAttackIndex++;

        _animInstance_Boss->JumpToSection(_curAttackIndex);
    }
}

void ATFT_Monster_TB_CG::AttackStart()
{
    Super::AttackStart();

    SoundManager->Play("Monster_Boss_Swing", GetActorLocation());
}

void ATFT_Monster_TB_CG::AttackHit_Boss()
{
    FHitResult hitResult;
    FCollisionQueryParams params(NAME_None, false, this);

    float attackRange = 500.0f;
    float attackRadius = 100.0f;

    bool bResult = GetWorld()->SweepSingleByChannel(
        hitResult,
        GetActorLocation(),
        GetActorLocation() + GetActorForwardVector() * attackRange,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel10,
        FCollisionShape::MakeSphere(attackRadius),
        params
    );

    FVector vec = GetActorForwardVector() * attackRange;
    FVector center = GetActorLocation() + vec * 0.5f;

    FColor drawColor = FColor::Green;

    if (bResult && hitResult.GetActor()->IsValidLowLevel())
    {
        float hpRatio = _statCom->HpRatio();
        float damageMultiplier = (hpRatio < 0.3f) ? 2.0f : 1.0f;

        float baseDamage = _statCom->GetAttackDamage();
        float damage = baseDamage * damageMultiplier;

        FDamageEvent damageEvent;
        hitResult.GetActor()->TakeDamage(damage, damageEvent, GetController(), this);
        _hitPoint = hitResult.ImpactPoint;
        drawColor = FColor::Red;

        EffectManager->Play("N_Monster_Boss_Attack_Hit", 1, _hitPoint);
    }

    DrawDebugSphere(GetWorld(), center, attackRadius, 20, drawColor, false, 2.0f);
}

void ATFT_Monster_TB_CG::DropItem()
{
    Super::DropItem();
}

void ATFT_Monster_TB_CG::DeathStart()
{
    Super::DeathStart();

    SoundManager->Play("Monster_Boss_Death", GetActorLocation());

    _animInstance_Boss->_deathStartDelegate.RemoveAll(this);
}

void ATFT_Monster_TB_CG::Boss_DeathEnd()
{
    this->SetActorHiddenInGame(true);

    _animInstance_Boss->_bossDeathEndDelegate.RemoveAll(this);
}

void ATFT_Monster_TB_CG::BossDisable()
{
    PrimaryActorTick.bCanEverTick = false;
    auto controller = GetController();
    if (controller != nullptr) GetController()->UnPossess();

    if (HpBarWidgetInstance)
    {
        HpBarWidgetInstance->RemoveFromParent();
        HpBarWidgetInstance = nullptr;
    }

    _animInstance_Boss->_deathEndDelegate.RemoveAll(this);
}

void ATFT_Monster_TB_CG::UpdateBlackboardTarget()
{
    float MaxDamage = 0.0f;
    AActor* TargetActor = nullptr;

    if (TotalDamageFromPlayer > MaxDamage && TargetPlayer != nullptr)
    {
        MaxDamage = TotalDamageFromPlayer;
        TargetActor = TargetPlayer;
    }
    if (TotalDamageFromKnight > MaxDamage && TargetKnight != nullptr)
    {
        MaxDamage = TotalDamageFromKnight;
        TargetActor = TargetKnight;
    }
    if (TotalDamageFromArcher > MaxDamage && TargetArcher != nullptr)
    {
        MaxDamage = TotalDamageFromArcher;
        TargetActor = TargetArcher;
    }

    ATFT_BossAI_Controller* AIController = Cast<ATFT_BossAI_Controller>(GetController());
    if (AIController && TargetActor)
    {
        UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
        if (BlackboardComp)
        {
            BlackboardComp->SetValueAsObject(FName(TEXT("Target")), TargetActor);
        }
    }
}

float ATFT_Monster_TB_CG::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    TotalDamageTaken += ActualDamage;

    FString DebugMessage;
    FColor MessageColor = FColor::Green;
    int32 MessageKey = 1;

    if (ATFT_Player* Player = Cast<ATFT_Player>(DamageCauser))
    {
        TotalDamageFromPlayer += ActualDamage;
        TargetPlayer = Player;
        
        MessageKey = 1;

        if (AggroComponent)
        {
            AggroComponent->AddDamage(ActualDamage, DamageCauser);
        }
    }
    else if (ATFT_TeamAI_Knight* Knight = Cast<ATFT_TeamAI_Knight>(DamageCauser))
    {
        TotalDamageFromKnight += ActualDamage;
        TargetKnight = Knight;
        
        MessageKey = 2;
    }
    else if (ATFT_TeamAI_Archer* Archer = Cast<ATFT_TeamAI_Archer>(DamageCauser))
    {
        TotalDamageFromArcher += ActualDamage;
        TargetArcher = Archer;
        
        MessageKey = 3;
    }
    else
    {
        
        MessageKey = 4;
    }

    const float TimeToDisplay = 500.0f;

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(MessageKey, TimeToDisplay, MessageColor, DebugMessage);
    }

    UpdateBlackboardTarget();

    return ActualDamage;
}
