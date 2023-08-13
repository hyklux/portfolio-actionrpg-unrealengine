// Fill out your copyright notice in the Description page of Project Settings.


#include "StateManageComponent.h"

// Sets default values for this component's properties
UStateManageComponent::UStateManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateManageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateManageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateManageComponent::SetState(FGameplayTag newState)
{
	if (CurrentState != newState)
	{
		CurrentState = newState;
	}
}

FGameplayTag UStateManageComponent::GetCurrentState() const
{
	return CurrentState;
}

bool UStateManageComponent::IsCurrentStateEqualToAny(FGameplayTagContainer& statesToCheck)
{
	return statesToCheck.HasTagExact(CurrentState);
}

void UStateManageComponent::SetAction(FGameplayTag newAction)
{
	if (CurrentAction != newAction)
	{
		CurrentAction = newAction;
	}
}

FGameplayTag UStateManageComponent::GetCurrentAction() const
{
	return CurrentAction;
}

bool UStateManageComponent::IsCurrentActionEqualToAny(FGameplayTagContainer& actionsToCheck)
{
	return actionsToCheck.HasTagExact(CurrentAction);
}

