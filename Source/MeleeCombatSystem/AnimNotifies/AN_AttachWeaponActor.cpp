// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_AttachWeaponActor.h"
#include "../CombatComponent.h"
#include "../BaseWeapon.h"

void UAN_AttachWeaponActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    UCombatComponent* combatComponent = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

    if (IsValid(combatComponent))
    {
        ABaseWeapon* baseWeapon = combatComponent->GetMainWeapon();
        if (IsValid(baseWeapon))
        {
            ABaseEquippable* baseEquippable = Cast<ABaseEquippable>(baseWeapon);
            if (IsValid(baseEquippable))
            {
                baseEquippable->AttachActor(AttachSocketName);
            }
        }
    }
}
