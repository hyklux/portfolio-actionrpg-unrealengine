// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_PlayWorldCameraShake.generated.h"

class UCameraShakeBase;
/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API UAN_PlayWorldCameraShake : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UCameraShakeBase> ShakeClass;

	UPROPERTY(EditAnywhere)
		float InnerRadius = 0.f;

	UPROPERTY(EditAnywhere)
		float OuterRadius = 1000.f;

	UPROPERTY(EditAnywhere)
		float Falloff = 1.f;

};
