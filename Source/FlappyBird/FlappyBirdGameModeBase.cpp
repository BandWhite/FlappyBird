// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"

#include "BgActor.h"
#include "BirdGameStateBase.h"
#include "BirdPawn.h"
#include "PipelineActor.h"

AFlappyBirdGameModeBase::AFlappyBirdGameModeBase()
{
	//设置启动pawn
	DefaultPawnClass = ABirdPawn::StaticClass();
	//设置GameState
	GameStateClass = ABirdGameStateBase::StaticClass();
}

void AFlappyBirdGameModeBase::BeginPlay()
{
	//创建背景actor
	BgActor = GetWorld()->SpawnActor<ABgActor>(ABgActor::StaticClass(), FVector(0, -50, 0), FRotator::ZeroRotator);
	LandActor = GetWorld()->SpawnActor<ALandActor>(ALandActor::StaticClass(), FVector(0, 0, -270),
	                                               FRotator::ZeroRotator);

	PipelineActor = GetWorld()->SpawnActor<APipelineActor>(APipelineActor::StaticClass(), FVector(0, -2, 0),
	                                                       FRotator(0, 0, 0));
}
