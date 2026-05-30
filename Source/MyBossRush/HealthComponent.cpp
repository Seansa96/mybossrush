// Copyright Epic Games, Inc. All Rights Reserved.

#include "HealthComponent.h"

#include "Math/UnrealMathUtility.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	Shield = 0.0f;
	bHasDeathProtection = false;
	bIsDead = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	ClampValues();
	CheckForDepletion(true);
}

float UHealthComponent::ApplyDamage(float DamageAmount, bool bShieldPiercing, bool bCanTriggerDeath)
{
	if (DamageAmount <= 0.0f)
	{
		return 0.0f;
	}

	const float HealthBeforeDamage = CurrentHealth;
	float RemainingDamage = DamageAmount;

	if (!bShieldPiercing && Shield > 0.0f)
	{
		const float ShieldDamage = FMath::Min(Shield, RemainingDamage);
		Shield -= ShieldDamage;
		RemainingDamage -= ShieldDamage;
	}

	if (RemainingDamage > 0.0f)
	{
		CurrentHealth = FMath::Max(0.0f, CurrentHealth - RemainingDamage);
	}

	CheckForDepletion(bCanTriggerDeath);

	return HealthBeforeDamage - CurrentHealth;
}

float UHealthComponent::ApplyHealing(float HealingAmount, bool bOverhealing)
{
	if (HealingAmount <= 0.0f || bIsDead)
	{
		return 0.0f;
	}

	const float HealthBeforeHealing = CurrentHealth;
	float RemainingHealing = HealingAmount;

	if (Shield < 0.0f)
	{
		const float ShieldDebtHealing = FMath::Min(-Shield, RemainingHealing);
		Shield += ShieldDebtHealing;
		RemainingHealing -= ShieldDebtHealing;
	}

	if (RemainingHealing > 0.0f)
	{
		const float HealthCap = bOverhealing ? BIG_NUMBER : MaxHealth;
		CurrentHealth = FMath::Clamp(CurrentHealth + RemainingHealing, 0.0f, HealthCap);
	}

	ClampValues(bOverhealing);

	return CurrentHealth - HealthBeforeHealing;
}

float UHealthComponent::SetShield(float NewShield)
{
	Shield = FMath::Clamp(NewShield, -GetNegativeShieldDebtCap(), GetShieldCap());
	return Shield;
}

float UHealthComponent::AddShield(float ShieldAmount)
{
	return SetShield(Shield + ShieldAmount);
}

void UHealthComponent::ResetHealth()
{
	CurrentHealth = MaxHealth;
	Shield = 0.0f;
	bIsDead = false;
	ClampValues();
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

float UHealthComponent::GetShieldCap() const
{
	return MaxHealth * ShieldCapMultiplier;
}

float UHealthComponent::GetNegativeShieldDebtCap() const
{
	return MaxHealth * ShieldCapMultiplier;
}

void UHealthComponent::ClampValues(bool bAllowOverhealing)
{
	MaxHealth = FMath::Max(1.0f, MaxHealth);
	CurrentHealth = bAllowOverhealing ? FMath::Max(0.0f, CurrentHealth) : FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	Shield = FMath::Clamp(Shield, -GetNegativeShieldDebtCap(), GetShieldCap());
}

void UHealthComponent::CheckForDepletion(bool bCanTriggerDeath)
{
	if (bIsDead || CurrentHealth >= 1.0f || bHasDeathProtection || !bCanTriggerDeath)
	{
		return;
	}

	bIsDead = true;
	OnHealthComponentDepleted.Broadcast(this);
}
