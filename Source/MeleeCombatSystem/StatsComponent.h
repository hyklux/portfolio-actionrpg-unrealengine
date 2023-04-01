// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

UENUM()
enum class EStats : uint8
{
	None,
	Health,
	Stamina,
	Armor,
};

USTRUCT()
struct FBaseStat
{
	GENERATED_BODY()

	float BaseValue = 0.0f;
	float MaxValue = 0.0f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

private:
	UPROPERTY()
	TMap<EStats, FBaseStat> BaseStats;
	UPROPERTY()
	TMap<EStats, float> CurrentStats;
	UPROPERTY()
	float StaminaRegenRate = 2;

public:

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	void InitializeState();

	UFUNCTION(BlueprintCallable)
	void SetCurrentStatValue(EStats stat, float value);

	UFUNCTION(BlueprintCallable)
	float GetCurrentStatValue(EStats stat);

	UFUNCTION(BlueprintCallable)
	float GetMaxStatValue(EStats stat);

	UFUNCTION(BlueprintCallable)
	void ModifyCurrentStatValue(EStats stat, float value, bool shouldRegenerate);
	
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float inDamage);

	UFUNCTION(BlueprintCallable)
	void RegenStamina();

	UFUNCTION(BlueprintCallable)
	void StartRegen(EStats stat);
};
