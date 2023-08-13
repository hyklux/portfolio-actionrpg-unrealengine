// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_PauseAnims.h"

void UAN_PauseAnims::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    MeshComp->bPauseAnims = PauseAnims;
}