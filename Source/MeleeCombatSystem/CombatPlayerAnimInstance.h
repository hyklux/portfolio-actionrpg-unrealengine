// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceInterface.h"
#include "CombatPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API UCombatPlayerAnimInstance : public UAnimInstance, public IAnimInstanceInterface
{
	GENERATED_BODY()
	
public:
	virtual void UpdateCombatType(ECombatType inCombatType) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateCombatType_BP(ECombatType inCombatType);
};
