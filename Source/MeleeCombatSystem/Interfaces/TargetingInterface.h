// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBATSYSTEM_API ITargetingInterface
{
	GENERATED_BODY()

public:
	virtual bool CanBeTargeted() = 0;
	virtual void OnTargeted(bool inbTargeted) = 0;
};
