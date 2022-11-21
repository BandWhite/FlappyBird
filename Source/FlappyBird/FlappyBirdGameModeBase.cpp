// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

#include "BgActor.h"
#include "BirdPawn.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	//设置启动pawn
	DefaultPawnClass = ABirdPawn::StaticClass();
}

void AFlappyBirdGameModeBase::BeginPlay()
{
	//创建背景actor
	BgActor = GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(), FVector(0, -50, 0), FRotator::ZeroRotator);
}
