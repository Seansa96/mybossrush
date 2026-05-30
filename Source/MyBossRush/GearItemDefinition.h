// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GearItemDefinition.generated.h"

UENUM(BlueprintType)
enum class EGearSlot : uint8
{
	Weapon,
	Helmet,
	Chest,
	Boots,
	Hands,
	Legs
};

UENUM(BlueprintType)
enum class EGearStat : uint8
{
	Stamina,
	Armor,
	Intellect,
	Strength,
	Agility,
	CriticalStrike,
	AttackSpeed,
	Haste,
	CooldownReduction,
	Mastery,
	Lifesteal
};

USTRUCT(BlueprintType)
struct FGearStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear")
	EGearStat Stat = EGearStat::Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear")
	float Value = 0.0f;
};

USTRUCT(BlueprintType)
struct FAttackValueRange
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear", meta = (ClampMin = "0"))
	float MinDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear", meta = (ClampMin = "0"))
	float MaxDamage = 0.0f;
};

UCLASS(BlueprintType)
class MYBOSSRUSH_API UGearItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear", meta = (MultiLine = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear", meta = (ClampMin = "0"))
	int32 SellValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear")
	EGearSlot GearSlot = EGearSlot::Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gear")
	TArray<FGearStatModifier> StatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FAttackValueRange WeaponDamageRange;
};
