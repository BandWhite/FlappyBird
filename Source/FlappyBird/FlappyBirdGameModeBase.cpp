// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

#include "BirdPawn.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	//设置启动pawn
	DefaultPawnClass = ABirdPawn::StaticClass();

	
	
}
