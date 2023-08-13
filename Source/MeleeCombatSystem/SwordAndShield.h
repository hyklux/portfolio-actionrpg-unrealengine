// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "SwordAndShield.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API ASwordAndShield : public ABaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ShieldMesh;

	UPROPERTY(EditAnywhere)
		FName ShieldAttachSocket;

	UPROPERTY(EditAnywhere)
		FName ShieldHandSocket;

public:
	ASwordAndShield();
	virtual void ToggleWeaponCombat(bool inbEnableCombat) override;
	
	void AttachShield(FName inAttachSocket);
	virtual void OnEquipped() override;
	virtual void OnUnequipped() override;
};
