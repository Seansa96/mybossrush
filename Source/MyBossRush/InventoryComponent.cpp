// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryComponent.h"

#include "GearItemDefinition.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InitializeSlots();
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeSlots();
}

bool UInventoryComponent::AddItem(UGearItemDefinition* ItemDefinition)
{
	if (!ItemDefinition || IsFull())
	{
		return false;
	}

	for (TObjectPtr<UGearItemDefinition>& InventorySlot : InventorySlots)
	{
		if (!InventorySlot)
		{
			InventorySlot = ItemDefinition;
			OnInventoryChanged.Broadcast(this);
			return true;
		}
	}

	return false;
}

UGearItemDefinition* UInventoryComponent::RemoveItemAtIndex(int32 Index)
{
	if (!IsValidIndex(Index) || IsSlotEmpty(Index))
	{
		return nullptr;
	}

	UGearItemDefinition* RemovedItem = InventorySlots[Index];
	InventorySlots[Index] = nullptr;
	OnInventoryChanged.Broadcast(this);

	return RemovedItem;
}

bool UInventoryComponent::DeleteItemAtIndex(int32 Index)
{
	if (!IsValidIndex(Index) || IsSlotEmpty(Index))
	{
		return false;
	}

	InventorySlots[Index] = nullptr;
	OnInventoryChanged.Broadcast(this);

	return true;
}

bool UInventoryComponent::MoveItem(int32 FromIndex, int32 ToIndex)
{
	if (!IsValidIndex(FromIndex) || !IsValidIndex(ToIndex))
	{
		return false;
	}

	if (FromIndex == ToIndex)
	{
		OnInventoryChanged.Broadcast(this);
		return true;
	}

	InventorySlots.Swap(FromIndex, ToIndex);
	OnInventoryChanged.Broadcast(this);

	return true;
}

UGearItemDefinition* UInventoryComponent::GetItemAtIndex(int32 Index) const
{
	return IsValidIndex(Index) ? InventorySlots[Index] : nullptr;
}

bool UInventoryComponent::IsFull() const
{
	return GetCurrentItemCount() >= MaxInventorySize;
}

bool UInventoryComponent::IsValidIndex(int32 Index) const
{
	return InventorySlots.IsValidIndex(Index);
}

bool UInventoryComponent::IsSlotEmpty(int32 Index) const
{
	return !IsValidIndex(Index) || !InventorySlots[Index];
}

int32 UInventoryComponent::GetCurrentItemCount() const
{
	int32 ItemCount = 0;

	for (const UGearItemDefinition* InventorySlot : InventorySlots)
	{
		if (InventorySlot)
		{
			++ItemCount;
		}
	}

	return ItemCount;
}

int32 UInventoryComponent::GetMaxInventorySize() const
{
	return MaxInventorySize;
}

void UInventoryComponent::InitializeSlots()
{
	InventorySlots.SetNum(MaxInventorySize);
}
