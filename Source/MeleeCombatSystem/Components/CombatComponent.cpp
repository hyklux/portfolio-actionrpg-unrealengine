// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"
#include "BaseWeapon.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::SetMainWeapon(ABaseWeapon* newWeapon)
{
	if (IsValid(MainWeapon))
	{
		MainWeapon->OnUnequipped();
		MainWeapon->Destroy();
	}

	MainWeapon = newWeapon;
}

ABaseWeapon* UCombatComponent::GetMainWeapon() const
{
	return MainWeapon;
}

void UCombatComponent::SetCombatEnabled(bool enableCombat)
{
	bCombatEnabled = enableCombat;
}

void UCombatComponent::ResetAttack()
{
	AttackCount = 0;
	bAttackSaved = false;
}

void UCombatComponent::SetBlockingState(bool inbEnableBlocking)
{
}

void UCombatComponent::SetShieldWeapon(ABaseWeapon* inShield)
{
}

void UCombatComponent::SetShieldEquipped(bool inbEquipped)
{
}