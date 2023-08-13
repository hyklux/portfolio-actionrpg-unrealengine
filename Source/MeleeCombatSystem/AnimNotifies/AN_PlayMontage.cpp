// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_PlayMontage.h"

void UAN_PlayMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    MeshComp->GetAnimInstance()->Montage_Play(MontageToPlay, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontages);
}
