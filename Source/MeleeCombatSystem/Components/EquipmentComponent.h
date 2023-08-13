// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class ABaseEquippable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeEquipment();
	void PerformActionFromItem(FGameplayTag inItemTag);
	ABaseEquippable* GetEquippedItemByTag(FGameplayTag inItemTag);
	bool EquipItem(TSubclassOf<ABaseEquippable> inEquipment);
	void UnequipItem(ABaseEquippable* inEquipmentToUnequip);
public:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEquippable>> StartingEquipment;

	UPROPERTY(EditAnywhere)
		TArray<ABaseEquippable*> EquippedItems;
};
