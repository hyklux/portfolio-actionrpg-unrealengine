// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UENUM()
enum class EMovementSpeedMode : uint8
{
	Walking,
	Jogging,
	Sprinting,
};

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
	bool CombatEnabled = false;
	
public:
	UPROPERTY()
	int AttackCount = 0;
	UPROPERTY()
	bool IsAttackSaved = false;
	UPROPERTY()
	bool IsAttacking = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void SetMainWeapon(ABaseWeapon* newWeapon);
	
	UFUNCTION(BlueprintCallable)
	ABaseWeapon* GetMainWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SetCombatEnabled(bool enableCombat);
	
	UFUNCTION(BlueprintCallable)
	bool IsCombatEnabled() const;
	
	UFUNCTION(BlueprintCallable)
	void ResetAttack();
		
};
