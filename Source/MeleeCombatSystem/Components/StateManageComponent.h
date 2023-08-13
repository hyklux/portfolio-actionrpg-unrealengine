// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "StateManageComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UStateManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateManageComponent();

private:
	FGameplayTag CurrentState;
	FGameplayTag CurrentAction;

public:


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetState(FGameplayTag newState);

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetCurrentState() const;

	UFUNCTION(BlueprintCallable)
	bool IsCurrentStateEqualToAny(FGameplayTagContainer& statesToCheck);

	UFUNCTION(BlueprintCallable)
	void SetAction(FGameplayTag newAction);

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetCurrentAction() const;

	UFUNCTION(BlueprintCallable)
	bool IsCurrentActionEqualToAny(FGameplayTagContainer& actionsToCheck);
};
