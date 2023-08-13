// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_CollisionTrace.h"
#include "../CombatInterface.h"


void UANS_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
        if (combatInterface)
        {
            combatInterface->ActivateCollision(CollisionPart);
        }
    }
}

void UANS_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
        if (combatInterface)
        {
            combatInterface->DeactivateCollision(CollisionPart);
        }
    }
}