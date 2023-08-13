// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEquippable.h"
#include "TypeDefine.h"
#include "Consumable.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBATSYSTEM_API AConsumable : public ABaseEquippable
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void PerformItemAction();
	void ConsumeItem();

public:
	UPROPERTY(EditAnywhere)
		UAnimMontage* UseItemMontage;

	UPROPERTY(EditAnywhere)
		int32 MaxNumberOfUses = 2;

	UPROPERTY(EditAnywhere)
		EStats Stat = EStats::None;

	UPROPERTY(EditAnywhere)
		float ModificationValue = 0.f;

	UPROPERTY(EditAnywhere)
		bool bShouldRegenerate = true;

	UPROPERTY(EditAnywhere)
		int32 CurrentNumberOfUses = 0;
};
