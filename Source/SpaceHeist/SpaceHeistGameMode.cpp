// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceHeistGameMode.h"
#include "SpaceHeistCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceHeistGameMode::ASpaceHeistGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
