#include "TFT_BT_Boss_FindTarget.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TFT_Monster_AIController.h"
#include "TFT_Creature.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"
#include "TFT_Player.h"
#include "TFT_TeamAI.h"

UTFT_BT_Boss_FindTarget::UTFT_BT_Boss_FindTarget()
{
    NodeName = TEXT("Find Target");
    Interval = 1.0f;
}

void UTFT_BT_Boss_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (currentPawn == nullptr)
        return;

    auto world = GetWorld();
    FVector center = currentPawn->GetActorLocation();
    float searchRadius = 1500.0f;

    if (world == nullptr)
        return;

    TArray<FOverlapResult> overlapResult;
    FCollisionQueryParams qparams(NAME_None, false, currentPawn);

    bool bResult = world->OverlapMultiByChannel
    (
        overlapResult,
        center,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(searchRadius),
        qparams
    );

    if (bResult)
    {
        for (auto& result : overlapResult)
        {

            auto myPlayer = Cast<ATFT_Player>(result.GetActor());
            if (myPlayer != nullptr)
            {
                auto myPlayerController = myPlayer->GetController();
                if (myPlayerController != nullptr && myPlayerController->IsPlayerController())
                {
                    OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), myPlayer);

                    return;
                }
            }


            auto myTeamAI = Cast<ATFT_TeamAI>(result.GetActor());
            if (myTeamAI != nullptr)
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), myTeamAI);

                return;
            }
        }

    }
    else
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
        
    }
}
