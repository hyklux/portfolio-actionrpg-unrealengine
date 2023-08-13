// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordAndShield.h"
#include "CombatComponent.h"
#include "GameFramework/Character.h"

ASwordAndShield::ASwordAndShield()
{
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	ShieldMesh->SetupAttachment(DefaultSceneRoot);
}

void ASwordAndShield::ToggleWeaponCombat(bool inbEnableCombat)
{
	Super::ToggleWeaponCombat(inbEnableCombat);

	AttachShield(inbEnableCombat ? ShieldHandSocket : ShieldAttachSocket);
}

void ASwordAndShield::AttachShield(FName inAttachSocket)
{
	if (IsValid(ShieldMesh))
	{
		ACharacter* character = Cast<ACharacter>(GetOwner());
		if (IsValid(character))
		{
			ShieldMesh->K2_AttachToComponent(character->GetMesh(), inAttachSocket, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		}
	}
}

void ASwordAndShield::OnEquipped()
{
	Super::OnEquipped();

	if (IsValid(CombatComponent))
	{
		AttachShield(CombatComponent->IsCombatEnabled() ? ShieldHandSocket : ShieldAttachSocket);
		CombatComponent->SetShieldEquipped(true);
	}
}

void ASwordAndShield::OnUnequipped()
{
	Super::OnUnequipped();

	if (IsValid(CombatComponent))
	{
		CombatComponent->SetShieldEquipped(false);
	}
}
