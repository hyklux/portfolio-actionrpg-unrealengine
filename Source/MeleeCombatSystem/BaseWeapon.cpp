// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "GameplayTagContainer.h"
#include "CombatComponent.h"
#include "StateManageComponent.h"

void ABaseWeapon::OnEquipped()
{
	CombatComponent = Cast<UCombatComponent>(GetOwner()->GetComponentByClass(UCombatComponent::StaticClass()));
	OwnerStateManager = Cast<UStateManageComponent>(GetOwner()->GetComponentByClass(UStateManageComponent::StaticClass()));
	AttachActor(CombatComponent->IsCombatEnabled() ? HandSocketName : AttachSocketName);
	CombatComponent->SetMainWeapon(this);
	MainWeaponCollisionComponent->SetCollisionMesh(GetItemMesh());
	MainWeaponCollisionComponent->AddActorToIgnore(GetOwner());
}

TArray<UAnimMontage*> ABaseWeapon::GetActionMontages(FGameplayTag characterAction)
{
	FName tagName = characterAction.GetTagName();
	
	if (tagName == TEXT("Character.Action.Attack.ChargeAttack"))
	{
		return ChargeAttackMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.FallingAttack"))
	{
		return FallingAttackMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.HeavyAttack"))
	{
		return HeavyAttackMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.LightAttack"))
	{
		return LightAttackMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.SprintAttack"))
	{
		return SprintAttackMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.Dodge"))
	{
		return DodgeMontages;
	}
	else if (tagName == TEXT("Character.Action.Attack.EnterCombat"))
	{
		TArray<UAnimMontage*> montages;
		montages.Push(EnterCombatMontage);
		return montages;
	}
	else if (tagName == TEXT("Character.Action.Attack.ExitCombat"))
	{
		TArray<UAnimMontage*> montages;
		montages.Push(ExitCombatMontage);
		return montages;
	}

	return TArray<UAnimMontage*>();
}

void ABaseWeapon::ActivateCollision(ECollisionPart collisionPart)
{
	MainWeaponCollisionComponent->ActivateCollision();
}

void ABaseWeapon::DeactivateCollision(ECollisionPart collisionPart)
{
	MainWeaponCollisionComponent->DeactivateCollision();
}

float ABaseWeapon::GetStatCostForAction()
{
	if (IsValid(OwnerStateManager))
	{
		float* statCostPtr = ActionStatCost.Find(OwnerStateManager->GetCurrentAction());
		if (statCostPtr)
		{
			return *statCostPtr;
		}
		else
		{
			return 0.0f;
		}
	}
	else
	{
		return 0.0f;
	}
}

float ABaseWeapon::GetDamage()
{
	if (IsValid(OwnerStateManager))
	{
		float* multiplierPtr = ActionDamageMultiplier.Find(OwnerStateManager->GetCurrentAction());
		if (multiplierPtr)
		{
			return Damage * (*multiplierPtr);
		}
		else
		{
			return 0.0f;
		}
	}
	else
	{
		return Damage;
	}
}

void ABaseWeapon::ToggleCombat(bool enableCombat)
{
	CombatComponent->SetCombatEnabled(enableCombat);
	AttachActor(enableCombat ? HandSocketName : AttachSocketName);
}
