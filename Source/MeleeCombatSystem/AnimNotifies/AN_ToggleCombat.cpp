// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ToggleCombat.h"
#include "../CombatComponent.h"

void UAN_ToggleCombat::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    UCombatComponent* combatComponent = Cast<UCombatComponent>(MeshComp->GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));

    if (IsValid(combatComponent))
    {
        combatComponent->SetCombatEnabled(!combatComponent->IsCombatEnabled());
    }
}