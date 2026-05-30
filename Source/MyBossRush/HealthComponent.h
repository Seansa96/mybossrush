// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponentDepletedSignature, UHealthComponent*, HealthComponent);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "1.0"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "0.0"))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bHasDeathProtection;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FHealthComponentDepletedSignature OnHealthComponentDepleted;

	/** Returns health damage applied after shield absorption. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float ApplyDamage(float DamageAmount, bool bShieldPiercing = false, bool bCanTriggerDeath = true);

	/** Returns health restored after any negative shield debt is cleared. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float ApplyHealing(float HealingAmount, bool bOverhealing = false);

	/** Returns the clamped shield value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float SetShield(float NewShield);

	/** Returns the clamped shield value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float AddShield(float ShieldAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ResetHealth();

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDead() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetShieldCap() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetNegativeShieldDebtCap() const;

protected:
	virtual void BeginPlay() override;

private:
	static constexpr float ShieldCapMultiplier = 10.0f;

	bool bIsDead;

	void ClampValues(bool bAllowOverhealing = false);
	void CheckForDepletion(bool bCanTriggerDeath);
};
