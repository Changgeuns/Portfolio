#include "TFT_StateComponent.h"

UTFT_StateComponent::UTFT_StateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTFT_StateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UTFT_StateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UTFT_StateComponent::SetState(StateType type)
{
	switch (type)
	{
	case StateType::Airborne:
		bIsAirborne = true;
		UE_LOG(LogTemp, Log, TEXT("SetAirborne"));
		break;

	case StateType::Stun:
		bIsStun = true;
		UE_LOG(LogTemp, Log, TEXT("SetStun"));
		break;

	case StateType::Slow:
		bIsSlow = true;
		UE_LOG(LogTemp, Log, TEXT("SetSlow"));
		break;

	default:
		break;
	}
}

bool UTFT_StateComponent::GetState(StateType type)
{
	switch (type)
	{
	case StateType::Airborne:
		return bIsAirborne;

	case StateType::Stun:
		return bIsStun;

	case StateType::Slow:
		return bIsSlow;

	default:
		return false;
	}	
}

void UTFT_StateComponent::InitState()
{
	bIsAirborne = false;
	bIsStun = false;
	bIsSlow = false;
}

