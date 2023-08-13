// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TypeDefine.h"
#include "AnimInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBATSYSTEM_API IAnimInstanceInterface
{
	GENERATED_BODY()

public:
	virtual void UpdateCombatType(ECombatType inCombatType) = 0;
};
