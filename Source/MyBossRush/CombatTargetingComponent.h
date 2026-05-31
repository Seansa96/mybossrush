// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatTargetingComponent.generated.h"

class UHealthComponent;

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class MYBOSSRUSH_API UCombatTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCombatTargetingComponent();

	UFUNCTION(BlueprintCallable, Category = "Combat|Targeting")
	bool SetTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Combat|Targeting")
	void ClearTarget();

	UFUNCTION(BlueprintPure, Category = "Combat|Targeting")
	AActor* GetCurrentTarget() const;

	UFUNCTION(BlueprintPure, Category = "Combat|Targeting")
	bool HasValidTarget() const;

	UFUNCTION(BlueprintPure, Category = "Combat|Targeting")
	bool IsTargetAlive() const;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat|Targeting", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> CurrentTarget;

	UHealthComponent* GetTargetHealthComponent(AActor* Target) const;
	bool IsTargetableActor(AActor* Target) const;
};
