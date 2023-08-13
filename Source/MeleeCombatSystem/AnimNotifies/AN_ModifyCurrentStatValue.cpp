// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ModifyCurrentStatValue.h"
#include "../StatsComponent.h"

void UAN_ModifyCurrentStatValue::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    UStatsComponent* statsComponent = Cast<UStatsComponent>(MeshComp->GetOwner()->GetComponentByClass(UStatsComponent::StaticClass()));

    if (IsValid(statsComponent))
    {
        statsComponent->ModifyCurrentStatValue(Stat, Value, bShouldRegenerate);
    }
}