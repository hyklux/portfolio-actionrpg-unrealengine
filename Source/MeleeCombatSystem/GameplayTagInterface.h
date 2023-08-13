// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagInterface.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameplayTagInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBATSYSTEM_API IGameplayTagInterface
{
	GENERATED_BODY()

public:
	virtual FGameplayTagContainer GetOwnedGameplayTags() = 0;

	virtual bool HasMatchingGameplayTag(FGameplayTag inTagToCheck) = 0;
};
