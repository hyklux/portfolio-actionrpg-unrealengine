// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MELEECOMBATSYSTEM_API TypeDefine
{
public:
	TypeDefine();
	~TypeDefine();
};

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	None,
	LightSword,
	GreatSword,
	DualSowrds,
};

UENUM(BlueprintType)
enum class ECollisionPart : uint8
{
	MainWeapon,
	OffHandWeapon,
	RightFoot,
};

UENUM(BlueprintType)
enum class EMovementSpeedMode : uint8
{
	Walking,
	Jogging,
	Sprinting,
};

UENUM(BlueprintType)
enum class EStats : uint8
{
	None,
	Health,
	Stamina,
	Armor,
	Damage,
};

UENUM(BlueprintType)
enum class ERotationMode : uint8
{
	OrientToCamera,
	OrientToMovement,
};