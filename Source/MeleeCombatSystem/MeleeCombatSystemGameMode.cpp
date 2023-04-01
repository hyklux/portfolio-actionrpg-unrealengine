// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeleeCombatSystemGameMode.h"
#include "MeleeCombatSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMeleeCombatSystemGameMode::AMeleeCombatSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/CombatSystem/Blueprints/BP_CombatCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
