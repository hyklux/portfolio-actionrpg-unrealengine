// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"
#include "GameplayTagContainer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StateManageComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::InitializeState()
{
	for (auto iter = BaseStats.CreateConstIterator(); iter; ++iter)
	{
		SetCurrentStatValue(iter->Key, iter->Value.BaseValue);
	}
}

void UStatsComponent::SetCurrentStatValue(EStats stat, float value)
{
	CurrentStats[stat] = value;
}

float UStatsComponent::GetCurrentStatValue(EStats stat)
{
	if (BaseStats.Contains(stat))
	{
		return BaseStats.Find(stat)->MaxValue;
	}

	return 0.0f;
}

float UStatsComponent::GetMaxStatValue(EStats stat)
{
	if (CurrentStats.Contains(stat))
	{
		return *CurrentStats.Find(stat);
	}

	return 0.0f;
}

void UStatsComponent::ModifyCurrentStatValue(EStats stat, float value, bool shouldRegenerate)
{
	if(value == 0)
	{
		return;
	}

	float newValue = GetCurrentStatValue(stat) + value;
	newValue = FMath::Clamp(newValue, 0.0f, GetMaxStatValue(stat));
	
	SetCurrentStatValue(stat, newValue);

	if (shouldRegenerate)
	{
		StartRegen(stat);
	}
}

void UStatsComponent::TakeDamage(float inDamage)
{
	ModifyCurrentStatValue(EStats::Health, -1 * inDamage, true);

	if (GetCurrentStatValue(EStats::Health) <= 0)
	{
		if (UStateManageComponent* stateManageComponent = Cast<UStateManageComponent>(GetOwner()->GetComponentByClass(UStateManageComponent::StaticClass())))
		{
			FGameplayTag tag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Dead"), true);
			stateManageComponent->SetState(tag);
		}
	}
}

void UStatsComponent::RegenStamina()
{
	float newValue = GetCurrentStatValue(EStats::Stamina) + StaminaRegenRate;
	newValue = FMath::Clamp(newValue, 0.0f, GetMaxStatValue(EStats::Stamina));

	SetCurrentStatValue(EStats::Stamina, newValue);

	if (GetCurrentStatValue(EStats::Stamina) >= GetMaxStatValue(EStats::Stamina))
	{
		UKismetSystemLibrary::K2_ClearTimer(this, TEXT("RegenStamina"));
	}
}

void UStatsComponent::StartRegen(EStats stat)
{
	if (stat == EStats::Stamina)
	{
		UKismetSystemLibrary::K2_ClearTimer(this, TEXT("RegenStamina"));
		UKismetSystemLibrary::K2_SetTimer(this, TEXT("RegenStamina"), 0.1f, true, 1.5f, 0.0f);
	}
}

