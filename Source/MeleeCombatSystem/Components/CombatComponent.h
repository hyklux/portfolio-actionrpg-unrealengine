// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TypeDefine.h"
#include "CombatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnCombatToggled, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnBlockingSet, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnShieldEquippedSet, bool);

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

private:
	UPROPERTY()
	ABaseWeapon* MainWeapon;
	
	UPROPERTY()
	bool bCombatEnabled = false;
	UPROPERTY()
	int AttackCount = 0;
	UPROPERTY()
	bool bAttackSaved = false;
	UPROPERTY()
	bool bAttacking = false;
	UPROPERTY()
		bool bBlocking = false;
	UPROPERTY()
		bool bShieldEquipped = false;
public:

	FDelegate_OnCombatToggled OnCombatToggledDelegate;
	FDelegate_OnBlockingSet OnBlockingSetDelegate;
	FDelegate_OnShieldEquippedSet OnShieldEquippedSetDelegate;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void SetMainWeapon(ABaseWeapon* newWeapon);
	
	UFUNCTION(BlueprintCallable)
	ABaseWeapon* GetMainWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SetCombatEnabled(bool enableCombat);
	
	UFUNCTION(BlueprintCallable)
		bool IsCombatEnabled() const { return bCombatEnabled; }
	
	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	UFUNCTION(BlueprintCallable)
		void SetBlockingState(bool inbEnableBlocking);

	UFUNCTION(BlueprintCallable)
		void SetShieldWeapon(ABaseWeapon* inShield);

	UFUNCTION(BlueprintCallable)
		bool IsBlocking() const { return bBlocking; }

	UFUNCTION(BlueprintCallable)
		bool IsShieldEquipped() const { return bShieldEquipped; }

	UFUNCTION(BlueprintCallable)
		void SetShieldEquipped(bool inbEquipped);
};
