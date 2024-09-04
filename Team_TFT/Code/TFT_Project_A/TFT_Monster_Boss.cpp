#include "TFT_Monster_Boss.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "TFT_HpBar.h"
#include "TFT_AnimInstance_Monster.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "TFT_Monster_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_AggroComponent.h"
#include "TFT_TeamAI_Knight.h"
#include "TFT_TeamAI_Archer.h"
#include "TFT_Player.h"

#include "TFT_GameInstance.h"
#include "TFT_SoundManager.h"
#include "TFT_Effect_Manager.h"

ATFT_Monster_Boss::ATFT_Monster_Boss()
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
}

void ATFT_Monster_Boss::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    _animInstance_Boss = Cast<UTFT_AnimInstance_Monster>(GetMesh()->GetAnimInstance());

    if (_animInstance_Boss->IsValidLowLevel())
    {
        _animInstance_Boss->OnMontageEnded.AddDynamic(this, &ATFT_Creature::OnAttackEnded);
        _animInstance_Boss->_attackStartDelegate.AddUObject(this, &ATFT_Monster_Boss::AttackStart);
        _animInstance_Boss->_attackHitDelegate.AddUObject(this, &ATFT_Monster_Boss::AttackHit_Boss);
        _animInstance_Boss->_deathStartDelegate.AddUObject(this, &ATFT_Monster_Boss::DeathStart);
        _animInstance_Boss->_bossDeathEndDelegate.AddUObject(this, &ATFT_Monster_Boss::Boss_DeathEnd);
        _animInstance_Boss->_deathEndDelegate.AddUObject(this, &ATFT_Monster_Boss::BossDisable);
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

void ATFT_Monster_Boss::BeginPlay()
{
    Super::BeginPlay();

    _statCom->SetLevelAndInit(100);

    UpdateBlackboardTarget();
}

void ATFT_Monster_Boss::SetMesh(FString path)
{
    _meshCom->SetMesh(path);
}

void ATFT_Monster_Boss::Attack_AI()
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

void ATFT_Monster_Boss::AttackStart()
{
    Super::AttackStart();

    SoundManager->Play("Monster_Boss_Swing", GetActorLocation());
}

void ATFT_Monster_Boss::AttackHit_Boss()
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
        ECollisionChannel::ECC_GameTraceChannel3,
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
    else
    {
   
    }

  

}

void ATFT_Monster_Boss::DropItem()
{
    Super::DropItem();
}

void ATFT_Monster_Boss::DeathStart()
{
    Super::DeathStart();

    SoundManager->Play("Monster_Boss_Death", GetActorLocation());

    _animInstance_Boss->_deathStartDelegate.RemoveAll(this);
}

void ATFT_Monster_Boss::Boss_DeathEnd()
{
    this->SetActorHiddenInGame(true);

    _animInstance_Boss->_bossDeathEndDelegate.RemoveAll(this);
}

void ATFT_Monster_Boss::BossDisable()
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

void ATFT_Monster_Boss::UpdateBlackboardTarget()
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

    ATFT_Monster_AIController* AIController = Cast<ATFT_Monster_AIController>(GetController());
    if (AIController && TargetActor)
    {
        UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
        if (BlackboardComp)
        {
            BlackboardComp->SetValueAsObject(FName(TEXT("Target")), TargetActor);
        }
    }
}

float ATFT_Monster_Boss::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    TotalDamageTaken += ActualDamage;

    if (AggroComponent)
    {
        AggroComponent->AddDamage(ActualDamage, DamageCauser);
    }

    if (ATFT_Player* Player = Cast<ATFT_Player>(DamageCauser))
    {
        TotalDamageFromPlayer += ActualDamage;
        TargetPlayer = Player; 

        UE_LOG(LogTemp, Warning, TEXT("Boss received %f damage from Player. Total Damage from Player: %f, Total Damage Taken: %f"), ActualDamage, TotalDamageFromPlayer, TotalDamageTaken);
    }
    else if (ATFT_TeamAI_Knight* Knight = Cast<ATFT_TeamAI_Knight>(DamageCauser))
    {
        TotalDamageFromKnight += ActualDamage;
        TargetKnight = Knight;

        UE_LOG(LogTemp, Warning, TEXT("Boss received %f damage from Knight. Total Damage from Knight: %f, Total Damage Taken: %f"), ActualDamage, TotalDamageFromKnight, TotalDamageTaken);
    }
    else if (ATFT_TeamAI_Archer* Archer = Cast<ATFT_TeamAI_Archer>(DamageCauser))
    {
        TotalDamageFromArcher += ActualDamage;
        TargetArcher = Archer;

        UE_LOG(LogTemp, Warning, TEXT("Boss received %f damage from Archer. Total Damage from Archer: %f, Total Damage Taken: %f"), ActualDamage, TotalDamageFromArcher, TotalDamageTaken);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss received %f damage from an unknown source. Total Damage Taken: %f"), ActualDamage, TotalDamageTaken);
    }

    UpdateBlackboardTarget();

    return ActualDamage;
}
