// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../TypeDefine.h"
#include "AN_ModifyCurrentStatValue.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API UAN_ModifyCurrentStatValue : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
		EStats Stat = EStats::None;

	UPROPERTY(EditAnywhere)
		float Value = 0.f;

	UPROPERTY(EditAnywhere)
		bool bShouldRegenerate = true;
};
