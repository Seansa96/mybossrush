// Copyright Epic Games, Inc. All Rights Reserved.

#include "EquipmentComponent.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InitializeEquipmentSlots();
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeEquipmentSlots();
}

UGearItemDefinition* UEquipmentComponent::EquipItem(UGearItemDefinition* ItemDefinition)
{
	if (!ItemDefinition)
	{
		return nullptr;
	}

	return EquipItemToSlot(ItemDefinition, ItemDefinition->GearSlot);
}

UGearItemDefinition* UEquipmentComponent::EquipItemToSlot(UGearItemDefinition* ItemDefinition, EGearSlot Slot)
{
	if (!ItemDefinition || ItemDefinition->GearSlot != Slot || !IsKnownSlot(Slot))
	{
		return nullptr;
	}

	TObjectPtr<UGearItemDefinition>& EquippedItem = EquippedItems.FindChecked(Slot);
	UGearItemDefinition* PreviouslyEquippedItem = EquippedItem;
	EquippedItem = ItemDefinition;
	OnEquipmentChanged.Broadcast(this);

	return PreviouslyEquippedItem;
}

UGearItemDefinition* UEquipmentComponent::UnequipSlot(EGearSlot Slot)
{
	if (!IsKnownSlot(Slot) || !EquippedItems[Slot])
	{
		return nullptr;
	}

	UGearItemDefinition* PreviouslyEquippedItem = EquippedItems[Slot];
	EquippedItems[Slot] = nullptr;
	OnEquipmentChanged.Broadcast(this);

	return PreviouslyEquippedItem;
}

UGearItemDefinition* UEquipmentComponent::GetEquippedItem(EGearSlot Slot) const
{
	const TObjectPtr<UGearItemDefinition>* EquippedItem = EquippedItems.Find(Slot);
	return EquippedItem ? EquippedItem->Get() : nullptr;
}

bool UEquipmentComponent::IsSlotOccupied(EGearSlot Slot) const
{
	return GetEquippedItem(Slot) != nullptr;
}

bool UEquipmentComponent::CanEquipItem(UGearItemDefinition* ItemDefinition) const
{
	return ItemDefinition && IsKnownSlot(ItemDefinition->GearSlot);
}

void UEquipmentComponent::InitializeEquipmentSlots()
{
	if (!EquippedItems.Contains(EGearSlot::Weapon))
	{
		EquippedItems.Add(EGearSlot::Weapon, nullptr);
	}

	if (!EquippedItems.Contains(EGearSlot::Helmet))
	{
		EquippedItems.Add(EGearSlot::Helmet, nullptr);
	}

	if (!EquippedItems.Contains(EGearSlot::Chest))
	{
		EquippedItems.Add(EGearSlot::Chest, nullptr);
	}

	if (!EquippedItems.Contains(EGearSlot::Boots))
	{
		EquippedItems.Add(EGearSlot::Boots, nullptr);
	}

	if (!EquippedItems.Contains(EGearSlot::Hands))
	{
		EquippedItems.Add(EGearSlot::Hands, nullptr);
	}

	if (!EquippedItems.Contains(EGearSlot::Legs))
	{
		EquippedItems.Add(EGearSlot::Legs, nullptr);
	}
}

bool UEquipmentComponent::IsKnownSlot(EGearSlot Slot) const
{
	return EquippedItems.Contains(Slot);
}
