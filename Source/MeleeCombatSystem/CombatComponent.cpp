// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatComponent.h"
#include "BaseWeapon.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
	CombatEnabled = enableCombat;
}

bool UCombatComponent::IsCombatEnabled() const
{
	return CombatEnabled;
}

void UCombatComponent::ResetAttack()
{
	AttackCount = 0;
	IsAttackSaved = false;
}

