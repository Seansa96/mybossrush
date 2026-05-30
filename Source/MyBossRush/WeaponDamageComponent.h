// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponDamageComponent.generated.h"

class UEquipmentComponent;
class UGearItemDefinition;

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UWeaponDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponDamageComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon Damage")
	float GetWeaponDamageRoll() const;

	UFUNCTION(BlueprintPure, Category = "Combat|Weapon Damage")
	float GetWeaponMinDamage() const;

	UFUNCTION(BlueprintPure, Category = "Combat|Weapon Damage")
	float GetWeaponMaxDamage() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat|Weapon Damage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	const UGearItemDefinition* GetEquippedWeapon() const;
};
