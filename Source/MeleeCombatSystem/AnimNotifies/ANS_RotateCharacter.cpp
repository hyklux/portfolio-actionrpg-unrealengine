// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_RotateCharacter.h"
#include "../CombatInterface.h"

void UANS_RotateCharacter::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* actorComp = MeshComp->GetOwner();
	if (IsValid(actorComp))
	{
		ICombatInterface* combatInterface = Cast<ICombatInterface>(actorComp);

		if (combatInterface)
		{
			FRotator newRotation = FMath::RInterpConstantTo(actorComp->GetActorRotation(), combatInterface->GetDesiredRotation(), FrameDeltaTime, InterpSpeed);
			actorComp->SetActorRotation(newRotation);
		}
	}
}
