// Copyright Epic Games, Inc. All Rights Reserved.

#include "ResourceComponent.h"

#include "Math/UnrealMathUtility.h"

UResourceComponent::UResourceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	FResourceData ManaResource;
	ManaResource.ResourceType = EResourceType::Mana;
	ManaResource.CurrentValue = 100.0f;
	ManaResource.MaxValue = 100.0f;
	ManaResource.RegenPerSecond = 5.0f;
	ManaResource.bRegeneratesAutomatically = true;
	Resources.Add(ManaResource);
}

void UResourceComponent::BeginPlay()
{
	Super::BeginPlay();

	ClampResources();
	UpdateTickEnabled();
}

void UResourceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (FResourceData& Resource : Resources)
	{
		if (!Resource.bRegeneratesAutomatically || Resource.RegenPerSecond <= 0.0f || Resource.CurrentValue >= Resource.MaxValue)
		{
			continue;
		}

		const float OldValue = Resource.CurrentValue;
		Resource.CurrentValue = FMath::Clamp(Resource.CurrentValue + (Resource.RegenPerSecond * DeltaTime), 0.0f, Resource.MaxValue);
		BroadcastResourceChanged(Resource.ResourceType, OldValue, Resource.CurrentValue);
	}
}

bool UResourceComponent::AddResource(EResourceType Type, float Amount)
{
	if (Amount < 0.0f)
	{
		return false;
	}

	FResourceData* Resource = FindResource(Type);
	if (!Resource)
	{
		return false;
	}

	const float OldValue = Resource->CurrentValue;
	Resource->CurrentValue = FMath::Clamp(Resource->CurrentValue + Amount, 0.0f, Resource->MaxValue);
	BroadcastResourceChanged(Type, OldValue, Resource->CurrentValue);

	return true;
}

bool UResourceComponent::SpendResource(EResourceType Type, float Amount)
{
	if (!CanSpendResource(Type, Amount))
	{
		return false;
	}

	FResourceData* Resource = FindResource(Type);
	const float OldValue = Resource->CurrentValue;
	Resource->CurrentValue = FMath::Clamp(Resource->CurrentValue - Amount, 0.0f, Resource->MaxValue);
	BroadcastResourceChanged(Type, OldValue, Resource->CurrentValue);

	return true;
}

bool UResourceComponent::CanSpendResource(EResourceType Type, float Amount) const
{
	const FResourceData* Resource = FindResource(Type);
	return Resource && Amount >= 0.0f && Resource->CurrentValue >= Amount;
}

float UResourceComponent::GetCurrentResource(EResourceType Type) const
{
	const FResourceData* Resource = FindResource(Type);
	return Resource ? Resource->CurrentValue : 0.0f;
}

float UResourceComponent::GetMaxResource(EResourceType Type) const
{
	const FResourceData* Resource = FindResource(Type);
	return Resource ? Resource->MaxValue : 0.0f;
}

bool UResourceComponent::SetResource(EResourceType Type, float NewValue)
{
	FResourceData* Resource = FindResource(Type);
	if (!Resource)
	{
		return false;
	}

	const float OldValue = Resource->CurrentValue;
	Resource->CurrentValue = FMath::Clamp(NewValue, 0.0f, Resource->MaxValue);
	BroadcastResourceChanged(Type, OldValue, Resource->CurrentValue);

	return true;
}

bool UResourceComponent::SetMaxResource(EResourceType Type, float NewMax)
{
	FResourceData* Resource = FindResource(Type);
	if (!Resource)
	{
		return false;
	}

	const float OldValue = Resource->CurrentValue;
	Resource->MaxValue = FMath::Max(0.0f, NewMax);
	Resource->CurrentValue = FMath::Clamp(Resource->CurrentValue, 0.0f, Resource->MaxValue);
	BroadcastResourceChanged(Type, OldValue, Resource->CurrentValue);
	UpdateTickEnabled();

	return true;
}

bool UResourceComponent::HasResource(EResourceType Type) const
{
	return FindResource(Type) != nullptr;
}

FResourceData* UResourceComponent::FindResource(EResourceType Type)
{
	return Resources.FindByPredicate([Type](const FResourceData& Resource)
	{
		return Resource.ResourceType == Type;
	});
}

const FResourceData* UResourceComponent::FindResource(EResourceType Type) const
{
	return Resources.FindByPredicate([Type](const FResourceData& Resource)
	{
		return Resource.ResourceType == Type;
	});
}

void UResourceComponent::ClampResources()
{
	for (FResourceData& Resource : Resources)
	{
		Resource.MaxValue = FMath::Max(0.0f, Resource.MaxValue);
		Resource.CurrentValue = FMath::Clamp(Resource.CurrentValue, 0.0f, Resource.MaxValue);
		Resource.RegenPerSecond = FMath::Max(0.0f, Resource.RegenPerSecond);
	}
}

void UResourceComponent::UpdateTickEnabled()
{
	bool bShouldTick = false;

	for (const FResourceData& Resource : Resources)
	{
		if (Resource.bRegeneratesAutomatically && Resource.RegenPerSecond > 0.0f)
		{
			bShouldTick = true;
			break;
		}
	}

	SetComponentTickEnabled(bShouldTick);
}

void UResourceComponent::BroadcastResourceChanged(EResourceType Type, float OldValue, float NewValue)
{
	if (!FMath::IsNearlyEqual(OldValue, NewValue))
	{
		OnResourceChanged.Broadcast(this, Type, OldValue, NewValue);
	}
}
