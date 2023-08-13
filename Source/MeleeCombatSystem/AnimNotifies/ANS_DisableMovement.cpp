// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_DisableMovement.h"
#include "GameFramework/CharacterMovementComponent.h"

void UANS_DisableMovement::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ACharacter* character = Cast<ACharacter>(owner);
        if (IsValid(character))
        {
            character->GetCharacterMovement()->DisableMovement();
        }
    }
}

void UANS_DisableMovement::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    AActor* owner = MeshComp->GetOwner();
    if (IsValid(owner))
    {
        ACharacter* character = Cast<ACharacter>(owner);
        if (IsValid(character))
        {
            character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking, 0);
        }
    }
}
