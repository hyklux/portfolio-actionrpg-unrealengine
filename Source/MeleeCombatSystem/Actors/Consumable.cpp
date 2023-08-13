// Fill out your copyright notice in the Description page of Project Settings.


#include "Consumable.h"
#include "CombatInterface.h"
#include "StatsComponent.h"

void AConsumable::BeginPlay()
{
	Super::BeginPlay();

	CurrentNumberOfUses = MaxNumberOfUses;
}

void AConsumable::PerformItemAction()
{
	if (CurrentNumberOfUses > 0)
	{
		AActor* owner = GetOwner();
		if (IsValid(owner))
		{
			ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
			if (combatInterface)
			{
				combatInterface->PerformCustomAction(FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Use Item")), FGameplayTag::RequestGameplayTag(TEXT("Character.State.GeneralActionState")), UseItemMontage, false);
			}
		}
	}
}

void AConsumable::ConsumeItem()
{
	Super::BeginPlay();

	CurrentNumberOfUses--;

	AActor* owner = GetOwner();
	if (IsValid(owner))
	{
		ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
		if (combatInterface)
		{
			combatInterface->UpdateHealthPotionAmount(CurrentNumberOfUses);
		}

		UStatsComponent* statsComponent = Cast<UStatsComponent>(owner->GetComponentByClass(UStatsComponent::StaticClass()));
		if (IsValid(statsComponent))
		{
			statsComponent->ModifyCurrentStatValue(Stat, ModificationValue, bShouldRegenerate);
		}
	}
}