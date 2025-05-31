// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_TaskGameMode.h"
#include "Test_TaskCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveWidget.h"

ATest_TaskGameMode::ATest_TaskGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
