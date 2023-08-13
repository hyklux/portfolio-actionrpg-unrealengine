// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_IFrames.h"
#include "../CombatInterface.h"

void UANS_IFrames::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
        if (combatInterface)
        {
            combatInterface->SetIFrames(true);
        }
    }
}

void UANS_IFrames::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
        if (combatInterface)
        {
            combatInterface->SetIFrames(false);
        }
    }
}