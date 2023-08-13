// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ConsumeItem.h"
#include "../EquipmentComponent.h"
#include "../Consumable.h"

void UAN_ConsumeItem::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        UEquipmentComponent* equipmentComponent = Cast<UEquipmentComponent>(owner->GetComponentByClass(UEquipmentComponent::StaticClass()));
        if (IsValid(equipmentComponent))
        {
            AConsumable* consumable = Cast<AConsumable>(equipmentComponent->GetEquippedItemByTag(ItemTagToConsume));
            if (IsValid(consumable))
            {
                consumable->ConsumeItem();
            }
        }
    }
}
