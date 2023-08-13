// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_ApplyRadialDamage.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "AIController.h"

void UAN_ApplyRadialDamage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    AActor* owner = MeshComp->GetOwner();
    TArray<AActor*> ignoreActors = { owner };
    if (IsValid(owner))
    {
        UGameplayStatics::ApplyRadialDamage(GetWorld(), BaseDamage, MeshComp->GetSocketLocation(LocationSocketName), DamageRadius, DamageTypeClass, ignoreActors, owner, owner->GetInstigatorController());
    }
}