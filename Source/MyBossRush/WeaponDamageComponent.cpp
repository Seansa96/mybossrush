// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponDamageComponent.h"

#include "EquipmentComponent.h"
#include "GearItemDefinition.h"
#include "Math/UnrealMathUtility.h"

UWeaponDamageComponent::UWeaponDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponDamageComponent::BeginPlay()
{
	Super::BeginPlay();
	
	EquipmentComponent = GetOwner()->FindComponentByClass<UEquipmentComponent>();

	ensureMsgf(EquipmentComponent, TEXT("WeaponDamageComponent requires an 
		EquipmentComponent on the same Actor."));
}

float UWeaponDamageComponent::GetWeaponDamageRoll() const
{
	const float MinDamage = GetWeaponMinDamage();
	const float MaxDamage = GetWeaponMaxDamage();

	if (MaxDamage <= 0.0f)
	{
		return 0.0f;
	}

	return FMath::FRandRange(FMath::Min(MinDamage, MaxDamage), FMath::Max(MinDamage, MaxDamage));
}

float UWeaponDamageComponent::GetWeaponMinDamage() const
{
	const UGearItemDefinition* EquippedWeapon = GetEquippedWeapon();
	return EquippedWeapon ? EquippedWeapon->WeaponDamageRange.MinDamage : 0.0f;
}

float UWeaponDamageComponent::GetWeaponMaxDamage() const
{
	const UGearItemDefinition* EquippedWeapon = GetEquippedWeapon();
	return EquippedWeapon ? EquippedWeapon->WeaponDamageRange.MaxDamage : 0.0f;
}

const UGearItemDefinition* UWeaponDamageComponent::GetEquippedWeapon() const
{
	if (!EquipmentComponent)
	{
		return nullptr;
	}

	return EquipmentComponent->GetEquippedItem(EGearSlot::Weapon);
}
