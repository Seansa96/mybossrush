// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GearItemDefinition.h"
#include "EquipmentComponent.generated.h"

class UEquipmentComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipmentChangedSignature, UEquipmentComponent*, EquipmentComponent);

UCLASS(ClassGroup=(Equipment), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEquipmentComponent();

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FEquipmentChangedSignature OnEquipmentChanged;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UGearItemDefinition* EquipItem(UGearItemDefinition* ItemDefinition);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UGearItemDefinition* EquipItemToSlot(UGearItemDefinition* ItemDefinition, EGearSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	UGearItemDefinition* UnequipSlot(EGearSlot Slot);

	UFUNCTION(BlueprintPure, Category = "Equipment")
	UGearItemDefinition* GetEquippedItem(EGearSlot Slot) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsSlotOccupied(EGearSlot Slot) const;

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool CanEquipItem(UGearItemDefinition* ItemDefinition) const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TMap<EGearSlot, TObjectPtr<UGearItemDefinition>> EquippedItems;

	void InitializeEquipmentSlots();
	bool IsKnownSlot(EGearSlot Slot) const;
};
