// Fill out your copyright notice in the Description page of Project Settings.

#include "AN_RotateToTarget.h"
#include "../CombatInterface.h"

void UAN_RotateToTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    ICombatInterface* combatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());

    if (combatInterface)
    {
        combatInterface->RotateToTarget();
    }
}