// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "BaseEquippable.h"
#include "CollisionComponent.h"
#include "TypeDefine.h"
#include "BaseWeapon.generated.h"

class UCombatComponent;
class UStateManageComponent;
class UStatsComponent;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API ABaseWeapon : public ABaseEquippable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCollisionComponent* MainWeaponCollisionComponent;

public:
	//Attack Anim Montages
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> LightAttackMontages;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> HeavyAttackMontages;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> ChargeAttackMontages;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> FallingAttackMontages;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> SprintAttackMontages;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> DodgeMontages;
	UPROPERTY(EditAnywhere)
	UAnimMontage* EnterCombatMontage;
	UPROPERTY(EditAnywhere)
	UAnimMontage* ExitCombatMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> BlockAttackMontages;

	UPROPERTY(EditAnywhere)
	FName HandSocketName;
	UPROPERTY(EditAnywhere)
	ECombatType CombatType;
	UPROPERTY(EditAnywhere)
	bool CanBlock;

	UPROPERTY()
	UCombatComponent* CombatComponent;
	UPROPERTY()
	UStateManageComponent* OwnerStateManager;
	UPROPERTY()
	UStatsComponent* OwnerStatsComponent;

	//Combat Data
	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, float> ActionStatCost;
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, float> ActionDamageMultiplier;

public:
	ABaseWeapon();

	virtual void OnEquipped() override;
	TArray<UAnimMontage*> GetActionMontages(FGameplayTag characterAction);
	void ActivateCollision(ECollisionPart collisionPart);
	void DeactivateCollision(ECollisionPart collisionPart);
	float GetStatCostForAction();
	float GetDamage();
	void ToggleCombat(bool enableCombat);

	UFUNCTION()
	void OnHit(FHitResult inHitResult);

	UFUNCTION()
		void SimulateWeaponPhysics();

	UFUNCTION()
		virtual void ToggleWeaponCombat(bool inbEnableCombat);
};
