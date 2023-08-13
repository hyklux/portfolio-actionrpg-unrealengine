// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TypeDefine.h"
#include "TargetingComponent.generated.h"

class UCombatComponent;
class UCameraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetingComponent();

private:
	UCombatComponent* OwnerCombatComponent;
	bool IsTargeting;
	AActor* TargetActor;
	ERotationMode CurrentRotationMode = ERotationMode::OrientToCamera;

public:
	UCameraComponent* FollowCamera;
	ACharacter* OwnerCharacter;
	AController* OwnerController;
	float TargetingDistance = 900.0f;
	float TargetingRadius = 100.0f;
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	float TargetRotationInterpSpeed = 9.0f;
	ERotationMode DefaultRotationMode = ERotationMode::OrientToMovement;

	void EnableLockOn();
	void DisableLockOn();
	void ToggleLockOn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetIsTargeting(bool enableTargeting);

	UFUNCTION(BlueprintCallable)
	bool GetIsTargeting() const;

	UFUNCTION(BlueprintCallable)
	bool FindTarget(AActor*& foundTarget);

	UFUNCTION(BlueprintCallable)
	void SetTargetActor(AActor* newTargetActor);

	UFUNCTION(BlueprintCallable)
	AActor* GetTargetActor() const;

	UFUNCTION(BlueprintCallable)
	void UpdateTargetingControlRotation();

	UFUNCTION(BlueprintCallable)
	void SetRotationMode(ERotationMode newRotationMode);

	UFUNCTION(BlueprintCallable)
	ERotationMode GetRotationMode() const;

	UFUNCTION(BlueprintCallable)
	bool CanTargetActor(AActor* inTargetActor);

	UFUNCTION(BlueprintCallable)
	void UpdateRotationMode();
};
