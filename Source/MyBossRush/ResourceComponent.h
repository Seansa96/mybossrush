// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceComponent.generated.h"

class UResourceComponent;

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Mana,
	Energy,
	Rage,
	ComboPoints,
	HolyPower
};

USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ResourceType = EResourceType::Mana;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta = (ClampMin = "0.0"))
	float CurrentValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta = (ClampMin = "0.0"))
	float MaxValue = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta = (ClampMin = "0.0"))
	float RegenPerSecond = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	bool bRegeneratesAutomatically = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FResourceChangedSignature, UResourceComponent*, ResourceComponent, EResourceType, ResourceType, float, OldValue, float, NewValue);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UResourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UResourceComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	TArray<FResourceData> Resources;

	UPROPERTY(BlueprintAssignable, Category = "Resource")
	FResourceChangedSignature OnResourceChanged;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool AddResource(EResourceType Type, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SpendResource(EResourceType Type, float Amount);

	UFUNCTION(BlueprintPure, Category = "Resource")
	bool CanSpendResource(EResourceType Type, float Amount) const;

	UFUNCTION(BlueprintPure, Category = "Resource")
	float GetCurrentResource(EResourceType Type) const;

	UFUNCTION(BlueprintPure, Category = "Resource")
	float GetMaxResource(EResourceType Type) const;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SetResource(EResourceType Type, float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Resource")
	bool SetMaxResource(EResourceType Type, float NewMax);

	UFUNCTION(BlueprintPure, Category = "Resource")
	bool HasResource(EResourceType Type) const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FResourceData* FindResource(EResourceType Type);
	const FResourceData* FindResource(EResourceType Type) const;
	void ClampResources();
	void UpdateTickEnabled();
	void BroadcastResourceChanged(EResourceType Type, float OldValue, float NewValue);
};
