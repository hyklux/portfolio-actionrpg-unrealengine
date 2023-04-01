// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "BasicEquippable.h"
#include "CollisionComponent.h"
#include "BaseWeapon.generated.h"

UENUM()
enum class ECombatType : uint8
{
	None,
	LightSword,
	GreatSword,
	DualSowrds,
};

class UStateManageComponent;
class UCombatComponent;
class UAnimMontage;
/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API ABaseWeapon : public ABasicEquippable
{
	GENERATED_BODY()
	
private:
	UStateManageComponent* OwnerStateManager;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCollisionComponent> MainWeaponCollisionComponent;

public:
	FName HandSocketName;
	ECombatType CombatType;
	UCombatComponent* CombatComponent;
	TArray<UAnimMontage*> LightAttackMontages;
	TArray<UAnimMontage*> HeavyAttackMontages;
	TArray<UAnimMontage*> ChargeAttackMontages;
	TArray<UAnimMontage*> FallingAttackMontages;
	TArray<UAnimMontage*> SprintAttackMontages;
	TArray<UAnimMontage*> DodgeMontages;
	UAnimMontage* EnterCombatMontage;
	UAnimMontage* ExitCombatMontage;
	float Damage;
	TMap<FGameplayTag, float> ActionStatCost;
	TMap<FGameplayTag, float> ActionDamageMultiplier;

public:
	virtual void OnEquipped() override;
	TArray<UAnimMontage*> GetActionMontages(FGameplayTag characterAction);
	void ActivateCollision(ECollisionPart collisionPart);
	void DeactivateCollision(ECollisionPart collisionPart);
	float GetStatCostForAction();
	float GetDamage();
	void ToggleCombat(bool enableCombat);
};
