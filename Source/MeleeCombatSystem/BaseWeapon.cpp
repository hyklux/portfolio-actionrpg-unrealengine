// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "GameplayTagContainer.h"
#include "CombatComponent.h"
#include "StateManageComponent.h"
#include "StatsComponent.h"
#include "CombatInterface.h"
#include "AnimInstanceInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ABaseWeapon::ABaseWeapon()
{
	MainWeaponCollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("MainWeaponCollisionComponent"));
	MainWeaponCollisionComponent->OnHitDelegate.BindUObject(this, &ABaseWeapon::OnHit);
}

void ABaseWeapon::OnEquipped()
{
	Super::OnEquipped();

	AActor* owner = GetOwner();

	CombatComponent = Cast<UCombatComponent>(owner->GetComponentByClass(UCombatComponent::StaticClass()));
	if (CombatComponent)
	{
		CombatComponent->OnCombatToggledDelegate.AddUObject(this, &ABaseWeapon::ToggleWeaponCombat);
		OwnerStateManager = Cast<UStateManageComponent>(owner->GetComponentByClass(UStateManageComponent::StaticClass()));
		OwnerStatsComponent = Cast<UStatsComponent>(owner->GetComponentByClass(UStatsComponent::StaticClass()));
		
		AttachActor(CombatComponent->IsCombatEnabled() ? HandSocketName : AttachSocketName);
		CombatComponent->SetMainWeapon(this);
		
		ACharacter* character = Cast<ACharacter>(owner);
		IAnimInstanceInterface* animInterface = Cast<IAnimInstanceInterface>(character->GetMesh()->GetAnimInstance());
		if (animInterface)
		{
			animInterface->UpdateCombatType(CombatType);
		}

		MainWeaponCollisionComponent->SetCollisionMesh(GetItemMesh());
		MainWeaponCollisionComponent->AddActorToIgnore(owner);
	}	
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
	else if (tagName == TEXT("Character.Action.Attack.Block Attack"))
	{
		return BlockAttackMontages;
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

void ABaseWeapon::OnHit(FHitResult inHitResult)
{
	AActor* damagedActor = inHitResult.GetActor();
	if (IsValid(damagedActor))
	{
		ICombatInterface* combatInterface = Cast<ICombatInterface>(damagedActor);

		if (combatInterface)
		{
			UGameplayStatics::ApplyPointDamage(damagedActor, GetDamage(), GetOwner()->GetActorForwardVector(), inHitResult, GetInstigatorController(), this, NULL);
		}
	}
}

void ABaseWeapon::SimulateWeaponPhysics()
{
	UPrimitiveComponent* itemMesh = GetItemMesh();
	if (IsValid(itemMesh))
	{
		itemMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
		itemMesh->SetSimulatePhysics(false);
	}
}

void ABaseWeapon::ToggleWeaponCombat(bool inbEnableCombat)
{
	AttachActor(inbEnableCombat ? HandSocketName : AttachSocketName);
}
