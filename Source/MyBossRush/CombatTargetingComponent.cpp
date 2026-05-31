// Copyright Epic Games, Inc. All Rights Reserved.

#include "CombatTargetingComponent.h"

#include "HealthComponent.h"
#include "TargetableInterface.h"

UCombatTargetingComponent::UCombatTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentTarget = nullptr;
}

bool UCombatTargetingComponent::SetTarget(AActor* Target)
{
	if (!IsTargetableActor(Target) || !GetTargetHealthComponent(Target))
	{
		return false;
	}

	CurrentTarget = Target;
	return true;
}

void UCombatTargetingComponent::ClearTarget()
{
	CurrentTarget = nullptr;
}

AActor* UCombatTargetingComponent::GetCurrentTarget() const
{
	return CurrentTarget;
}

bool UCombatTargetingComponent::HasValidTarget() const
{
	return IsTargetableActor(CurrentTarget) && GetTargetHealthComponent(CurrentTarget);
}

bool UCombatTargetingComponent::IsTargetAlive() const
{
	const UHealthComponent* TargetHealthComponent = GetTargetHealthComponent(CurrentTarget);
	return TargetHealthComponent && !TargetHealthComponent->IsDead();
}

UHealthComponent* UCombatTargetingComponent::GetTargetHealthComponent(AActor* Target) const
{
	return Target ? Target->FindComponentByClass<UHealthComponent>() : nullptr;
}

bool UCombatTargetingComponent::IsTargetableActor(AActor* Target) const
{
	return Target && Target->GetClass()->ImplementsInterface(UTargetableInterface::StaticClass());
}
