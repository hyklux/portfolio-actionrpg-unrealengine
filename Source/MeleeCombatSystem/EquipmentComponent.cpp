


#include "EquipmentComponent.h"
#include "BaseEquippable.h"
#include "Kismet/KismetSystemLibrary.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEquipmentComponent::InitializeEquipment()
{
	for (ABaseEquippable* baseEquippable : EquippedItems)
	{
		UnequipItem(baseEquippable);
	}

	for (TSubclassOf<ABaseEquippable> baseEquippableClass : StartingEquipment)
	{
		if (UKismetSystemLibrary::IsValidClass(baseEquippableClass->GetClass()))
		{
			EquipItem(baseEquippableClass);
		}
	}
}

void UEquipmentComponent::PerformActionFromItem(FGameplayTag inItemTag)
{
	for (ABaseEquippable* baseEquippable : EquippedItems)
	{
		if (IsValid(baseEquippable))
		{
			if(baseEquippable->HasMatchingGameplayTag(inItemTag))
			{
				//khy todo
				//baseEquippable->PerformItemAction();
			}
		}
	}
}

ABaseEquippable* UEquipmentComponent::GetEquippedItemByTag(FGameplayTag inItemTag)
{
	for (ABaseEquippable* baseEquippable : EquippedItems)
	{
		if (IsValid(baseEquippable))
		{
			if (baseEquippable->HasMatchingGameplayTag(inItemTag))
			{
				return baseEquippable;
			}
		}
	}

	return nullptr;
}

bool UEquipmentComponent::EquipItem(TSubclassOf<ABaseEquippable> inEquipment)
{
	if (UKismetSystemLibrary::IsValidClass(inEquipment->GetClass()))
	{
		for (ABaseEquippable* baseEquippable : EquippedItems)
		{
			if (baseEquippable->GetClass() == inEquipment->GetClass())
			{
				UnequipItem(baseEquippable);
			}
		}

		AActor* owner = GetOwner();
		APawn* ownerPawn = Cast<APawn>(owner);
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = owner;
		spawnParams.Instigator = ownerPawn;
		ABaseEquippable* equippedActor = GetWorld()->SpawnActor<ABaseEquippable>(inEquipment->GetClass(), owner->GetActorTransform(), spawnParams);
		if (IsValid(equippedActor))
		{
			EquippedItems.AddUnique(equippedActor);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void UEquipmentComponent::UnequipItem(ABaseEquippable* inEquipmentToUnequip)
{
	if (IsValid(inEquipmentToUnequip))
	{
		inEquipmentToUnequip->OnUnequipped();
		GetWorld()->DestroyActor(inEquipmentToUnequip);
	}
}

