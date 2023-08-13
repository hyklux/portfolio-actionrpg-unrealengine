// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_PlayWorldCameraShake.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"

void UAN_PlayWorldCameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (IsValid(MeshComp->GetOwner()))
    {
        UGameplayStatics::PlayWorldCameraShake(GetWorld(), ShakeClass, MeshComp->GetOwner()->GetActorLocation(), InnerRadius, OuterRadius, Falloff);
    }
}

