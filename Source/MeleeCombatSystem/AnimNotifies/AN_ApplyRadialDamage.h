// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_ApplyRadialDamage.generated.h"

class DamageType;
/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API UAN_ApplyRadialDamage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
		float BaseDamage = 0.f;

	UPROPERTY(EditAnywhere)
		FName LocationSocketName;

	UPROPERTY(EditAnywhere)
		float DamageRadius = 300.f;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> DamageTypeClass;
};
