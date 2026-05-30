// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoldComponent.h"

#include "Math/UnrealMathUtility.h"

UGoldComponent::UGoldComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentGold = 0;
}

void UGoldComponent::BeginPlay()
{
	Super::BeginPlay();

	SetGoldClamped(CurrentGold);
}

bool UGoldComponent::AddGold(int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	SetGoldClamped(static_cast<int64>(CurrentGold) + Amount);
	return true;
}

bool UGoldComponent::TrySpendGold(int32 Amount)
{
	if (Amount <= 0 || !CanAfford(Amount))
	{
		return false;
	}

	SetGoldClamped(CurrentGold - Amount);
	return true;
}

bool UGoldComponent::CanAfford(int32 Amount) const
{
	return Amount >= 0 && CurrentGold >= Amount;
}

void UGoldComponent::SetGoldClamped(int64 NewGold)
{
	const int32 OldGold = CurrentGold;
	CurrentGold = static_cast<int32>(FMath::Clamp<int64>(NewGold, 0, MAX_int32));

	if (CurrentGold != OldGold)
	{
		OnGoldChanged.Broadcast(this, OldGold, CurrentGold);
	}
}
