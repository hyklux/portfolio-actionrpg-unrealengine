// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API UAN_PlayMontage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* MontageToPlay;

	UPROPERTY(EditAnywhere)
		float InPlayRate = 1.f;

	UPROPERTY(EditAnywhere)
		EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength;

	UPROPERTY(EditAnywhere)
		float InTimeToStartMontageAt = 0.f;

	UPROPERTY(EditAnywhere)
		bool bStopAllMontages = true;
};
