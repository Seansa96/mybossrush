// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UGearItemDefinition;
class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryChangedSignature, UInventoryComponent*, InventoryComponent);

UCLASS(ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryChangedSignature OnInventoryChanged;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UGearItemDefinition* ItemDefinition);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UGearItemDefinition* RemoveItemAtIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool DeleteItemAtIndex(int32 Index);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool MoveItem(int32 FromIndex, int32 ToIndex);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UGearItemDefinition* GetItemAtIndex(int32 Index) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsFull() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsValidIndex(int32 Index) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	bool IsSlotEmpty(int32 Index) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetCurrentItemCount() const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetMaxInventorySize() const;

protected:
	virtual void BeginPlay() override;

private:
	static constexpr int32 MaxInventorySize = 30;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UGearItemDefinition>> InventorySlots;

	void InitializeSlots();
};
