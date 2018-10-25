// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ImmortalGameMode.h"
#include "DefaultCharacter.h"

AImmortalGameMode::AImmortalGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ADefaultCharacter::StaticClass();	
}
