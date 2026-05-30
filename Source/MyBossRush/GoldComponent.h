// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"

class UGoldComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGoldChangedSignature, UGoldComponent*, GoldComponent, int32, OldGold, int32, NewGold);

UCLASS(ClassGroup=(Currency), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGoldComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gold", meta = (ClampMin = "0"))
	int32 CurrentGold;

	UPROPERTY(BlueprintAssignable, Category = "Gold")
	FGoldChangedSignature OnGoldChanged;

	/** Returns true if positive gold was added. Rejects negative and zero amounts. */
	UFUNCTION(BlueprintCallable, Category = "Gold")
	bool AddGold(int32 Amount);

	/** Returns true if positive gold was spent. Rejects negative, zero, and unaffordable amounts. */
	UFUNCTION(BlueprintCallable, Category = "Gold")
	bool TrySpendGold(int32 Amount);

	/** Returns true if Amount is non-negative and CurrentGold is at least Amount. */
	UFUNCTION(BlueprintPure, Category = "Gold")
	bool CanAfford(int32 Amount) const;

protected:
	virtual void BeginPlay() override;

private:
	void SetGoldClamped(int64 NewGold);
};
