// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TypeDefine.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBATSYSTEM_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual bool PerformAction(FGameplayTag inActionTag, FGameplayTag inStateTag, int32 inMontageIndex, bool inbRandomIndex, float& outActionDuration) = 0;
	virtual bool PerformCustomAction(FGameplayTag inActionTag, FGameplayTag inStateTag, UAnimMontage* inMontage, bool inbAutoReset) = 0;
	virtual bool PerformAttack(FGameplayTag inAttackType, int32 inAttackIndex, bool inbRandomIndex, float& outAttackDuration) = 0;
	virtual void ActivateCollision(ECollisionPart inCollisionPart) = 0;
	virtual void DeactivateCollision(ECollisionPart inCollisionPart) = 0;
	virtual void ContinueAttack() = 0;
	virtual void ResetAttack() = 0;
	virtual FRotator GetDesiredRotation() = 0;
	virtual void ResetCombat() = 0;
	virtual bool CanReceiveDamage() = 0;
	virtual void SetCanMove(bool inbCanMove) = 0;
	virtual EMovementSpeedMode GetMovementSpeedMode() = 0;
	virtual void SetIFrames(bool inbEnableIFrames) = 0;
	virtual void RotateToTarget() = 0;
	virtual void UpdateHealthPotionAmount(int32 inAmount) = 0;

};
